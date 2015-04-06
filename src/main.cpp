#include "Hydra.h"
#include "Sprite.h"
#include <vector>
#include <unistd.h>
#include <stdio.h>
using namespace std;
using namespace Hydra;

enum dirs {left, right, up, down};

class ComicPanel
{
public:
    int posX;
    int posY;
    float velX; //Speed when traveling TO this panel!
    float velY;
    bool root;
    bool blank; //If true, don't render this panel - it's just an empty frame.
    string nextComic[4]; //The name of the next panel to be moved to given
    string name;
    Sprite* image;
};

ComicPanel* loadFromXML(pugi::xml_node configNode);
ComicPanel* switchToComic(vector<ComicPanel*> panels, string nextName);

Log* sysLog = Logger::getInstance()->getLog("sysLog");

int main(int argc, char* argv[])
{
	HydraEngine* engine = HydraEngine::getInstance();
	engine->init();

    vector<ComicPanel*> panels;
    //int currentX = 0, currentY = 0;
    //bool transitioning = false;
    //double scale = 1.0;
    //ComicPanel* currentComic;

    char cCurrentPath[FILENAME_MAX];
    cout << "CWD: " <<  getcwd(cCurrentPath, sizeof(cCurrentPath)) << endl;

    //Load all comics
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("Comic.xml");
    cout << "Loaded file Comic.xml with result: " << result.description() << endl;
    cout << "\nLoading panels...\n" << endl;

    for (pugi::xml_node comic = doc.child("Comics").child("panel"); comic; comic = comic.next_sibling())
    {
        ComicPanel* newPanel = loadFromXML(comic);
        panels.push_back(newPanel);
    }

    SDL_RenderClear(engine->getRenderer());

    //Render panels
    for (auto iter = panels.begin(); iter != panels.end(); iter++)
    {
        Sprite* image = (*iter)->image;
        image->render((*iter)->posX, (*iter)->posY);
    }
    SDL_RenderPresent(engine->getRenderer());

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }

    //Shutdown sequence
    cout << "\nFreeing images..." << endl;
    for (auto iter = panels.begin(); iter != panels.end(); iter++)
    {
        cout << "Freeing " << (*iter)->name << "..." << endl;
        (*iter)->image->free();
        delete *iter;
    }
    engine->shutdown();
}

ComicPanel* loadFromXML(pugi::xml_node configNode)
{
    //Assumes that this node is a "panel" node.
    ComicPanel* newPanel = new ComicPanel;
    newPanel->image = new Sprite;

    newPanel->name = configNode.attribute("name").as_string();
    newPanel->posX = configNode.child("position").attribute("x").as_int();
    newPanel->posY = configNode.child("position").attribute("y").as_int();
    newPanel->velX = configNode.child("vels").attribute("velX").as_int();
    newPanel->velY = configNode.child("vels").attribute("velY").as_int();
    newPanel->root = false; //Default value
    newPanel->root = configNode.child("root").attribute("enabled").as_bool();
    newPanel->blank = false; //Default value
    newPanel->blank = configNode.child("blank").attribute("enabled").as_bool();
    for (int i = 0; i < 4; i++)
        newPanel->nextComic[i] = "null"; //Signifies that there is no transition to a new comic. These are default values.

    newPanel->nextComic[dirs::up] =       configNode.child("dirs").child("up").attribute("nextComic").as_string();
    newPanel->nextComic[dirs::down] =     configNode.child("dirs").child("down").attribute("nextComic").as_string();
    newPanel->nextComic[dirs::left] =     configNode.child("dirs").child("left").attribute("nextComic").as_string();
    newPanel->nextComic[dirs::right] =    configNode.child("dirs").child("right").attribute("nextComic").as_string();


    cout << "Loaded panel " << newPanel->name << endl;
    if (newPanel->blank)
        return newPanel; //There is no image to load; skip loading an image.
    newPanel->image->loadFromFile(configNode.child("filename").attribute("str").as_string());
    cout << "Loaded file " << configNode.child("filename").attribute("str").as_string() << endl << endl;
    return newPanel;
}
