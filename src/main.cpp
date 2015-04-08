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
    int height;
    int width;
    float vel; //Speed when traveling TO this panel!    bool root;
    bool blank; //If true, don't render this panel - it's just an empty frame.
    bool root; //Is this comic a root?
    string nextComic[4]; //The name of the next panel to be moved to given
    string name;
    Sprite* image;
};

ComicPanel* loadFromXML(pugi::xml_node configNode);
ComicPanel* switchToComic(vector<ComicPanel*> panels, string nextName);
inline double getScaling(ComicPanel* panel, HydraEngine* engine);

Log* sysLog = Logger::getInstance()->getLog("sysLog");

int main(int argc, char* argv[])
{
	HydraEngine* engine = HydraEngine::getInstance();
	engine->init();

    vector<ComicPanel*> panels;
    bool quit = false;

    double currentX = 0, currentY = 0;
    double dX = 0, dY = 0;
    double scale = 1.0f;
    double scalingDiff = 0.0f; //How much to change by
    bool transitioning = false;
    ComicPanel* currentPanel;

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
        if (newPanel->root)
        {
            currentPanel = newPanel;
            scale = getScaling(currentPanel, engine); //The comic is to start out scaled to the root panel
        }
        panels.push_back(newPanel);
    }

    if (currentPanel == nullptr)
        cout << "Error - couldn't find the root panel! Have you specified one yet?" << endl;

    while (!quit && currentPanel != nullptr)
    {
        Timer fpsTimer;
        fpsTimer.start();
        fpsTimer.setInterval(1000.0f / 60.0f);

        //Does nothing overly special; it's just here for the quit command.
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        //Transitioning stuff
        if (!transitioning)
        {
            ComicPanel* nextPanel = nullptr;

            const Uint8* keystate = SDL_GetKeyboardState(nullptr);
            if (keystate[SDL_SCANCODE_DOWN])
                nextPanel = switchToComic(panels, currentPanel->nextComic[dirs::down]);
            if (keystate[SDL_SCANCODE_UP])
                nextPanel = switchToComic(panels, currentPanel->nextComic[dirs::up]);
            if (keystate[SDL_SCANCODE_LEFT])
                nextPanel = switchToComic(panels, currentPanel->nextComic[dirs::left]);
            if (keystate[SDL_SCANCODE_RIGHT])
                nextPanel = switchToComic(panels, currentPanel->nextComic[dirs::right]);

            if (nextPanel != nullptr)
            {
                currentPanel = nextPanel;
                transitioning = true;
                cout << "Switching panels to panel " << currentPanel->name;

                //Compute dX and dY values
                Vector2D dir;
                dir.rotate(atan2f((double)(currentPanel->posY - currentY), (double)(currentPanel->posX - currentX)));
                dir.setMag(currentPanel->vel);
                dX = dir.getX();
                dY = dir.getY();
            }
        }

        //Velocities in directions - uses a Vector2D for calculations (because TRIGONOMETRY!)
        if (transitioning)
        {
            Vector2D dir;
            dir.setX(abs((int)(scale * ((double)currentPanel->posX - currentX))));
            dir.setY(abs((int)(scale * ((double)currentPanel->posY - currentY))));
            scalingDiff = (getScaling(currentPanel, engine) - scale) / (dir.getMag() / (double)currentPanel->vel);

            scale += scalingDiff;
            currentX += dX * scale;
            currentY += dY * scale;

            if (dir.getMag() <= currentPanel->vel)
            {
                transitioning = false;
                currentX = (double)currentPanel->posX; //Absolute magic. Complete effing magic!
                currentY = (double)currentPanel->posY;
                scale= getScaling(currentPanel, engine); //Fix scaling
                cout << ". Viewer at " << currentX << ", " << currentY << ". Scale: " << getScaling(currentPanel, engine) << endl;
            }
        }

        //Rendering stuff
        SDL_RenderClear(engine->getRenderer());
        for (auto iter = panels.begin(); iter != panels.end(); iter++)
        {
            if ((*iter)->blank)
              continue;
            Sprite* image = (*iter)->image;
            image->render(((*iter)->posX - currentX) * scale,
                          ((*iter)->posY - currentY) * scale,
                          image->getH() * scale,
                          image->getW() * scale);
        }

        SDL_RenderPresent(engine->getRenderer());

        //Ensures 60 fps
        while (!fpsTimer.hasIntervalPassed());
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
    newPanel->vel = configNode.child("vel").attribute("value").as_float();
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
    {
        newPanel->width = configNode.child("dims").attribute("width").as_int();
        newPanel->height = configNode.child("dims").attribute("height").as_int();
        return newPanel; //There is no image to load; skip loading an image.
    }

    newPanel->image->loadFromFile(configNode.child("filename").attribute("str").as_string());
    cout << "Loaded file " << configNode.child("filename").attribute("str").as_string() << endl << endl;
    newPanel->height = newPanel->image->getH();
    newPanel->width = newPanel->image->getW();
    return newPanel;
}
ComicPanel* switchToComic(vector<ComicPanel*> panels, string nextName)
{
    //Given a name of a panel and a vector of pointers to panels, find a panel with the given name.
    //Returns nullptr if there is no such pointer

    //Dummy check - XML file should specify null if you don't want to switch to comic from a dir
    if (nextName == "null")
        return nullptr;

    for (auto iter = panels.begin(); iter != panels.end(); iter++)
    {
        if ((*iter)->name == nextName)
        {
            return *iter;
        }
    }

    cout << "Error switching panels: panel " << nextName << " does not exist." << endl;
    return nullptr; //Yeah, sorry, this panel doesn't exist.
}
double getScaling(ComicPanel* panel, HydraEngine* engine)
{
    //Figure out the scaling needed to fit this panel's largest dimension on the
    if (abs(engine->getWXSize() - panel->width) >= abs(engine->getWYSize() - panel->height))
        return (float)engine->getWXSize() / (float)panel->width;
    else
        return (float)engine->getWYSize() / (float)panel->height;
}
