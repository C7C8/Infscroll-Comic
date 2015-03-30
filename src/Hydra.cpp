#include "Hydra.h"

namespace Hydra
{
	HydraEngine* HydraEngine::instance = nullptr;
	HydraEngine* HydraEngine::getInstance()
	{
		if (instance == nullptr)
			instance = new HydraEngine;
		return instance;
	}
	HydraEngine::HydraEngine()
	{
	    systemLog = Logger::getInstance();
        systemLog->newLog("sysLog", "sysLog");

		wXSize = 800;
		wYSize = 600;
		window = nullptr;
		renderer = nullptr;
		wTitle = "Hydra 2D Game Engine V3";
	}
	bool HydraEngine::init()
	{
	    systemLog->log("Initializing Hydra Engine " + getVNumber() + " (prepare for a wild ride!)");
		SDL_Init(SDL_INIT_VIDEO); systemLog->log("Successfully initialized SDL");
		//TTF_Init();
		//IMG_Init(IMG_INIT_PNG);

		window = SDL_CreateWindow(wTitle.c_str(),  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		wXSize, wYSize, SDL_WINDOW_SHOWN);
		if (window == nullptr)
        {
            systemLog->log("Error: Failed to create SDL window!", error);
            return false;
        }

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
        {
            systemLog->log("Error: Failed to create renderer!", error);
            return false;
        }
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);	//Black

		srand((int)time(0));
		setWTitle("Hydra Engine " + getVNumber());
		systemLog->log("Successfully started the Hydra Engine!");
		
		Sprite::renderer = renderer;
		return true;
	}
	void HydraEngine::shutdown()
	{
	    systemLog->log("Shutting down Hydra Engine...");
		//IMG_Quit();
		//TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		window = nullptr;
		renderer = nullptr;
		systemLog->log("Successfully shut down Hydra Engine");
		systemLog->flushLogBuffers();
	}

	//Getters and setters
	void  HydraEngine::setWSize(Uint16 newXSize, Uint16 newYSize)
	{
		wXSize = newXSize;
		wYSize = newYSize;
		SDL_SetWindowSize(window, wXSize, wYSize);
	}
	Uint16 HydraEngine::getWXSize() const
	{
		return wXSize;
	}
	Uint16 HydraEngine::getWYSize() const
	{
		return wYSize;
	}
	void HydraEngine::setWTitle(string newTitle)
	{
		wTitle = newTitle;
		SDL_SetWindowTitle(window, wTitle.c_str());
		systemLog->log("Set window title to " + wTitle);
	}
	string HydraEngine::getWTitle() const
	{
		return wTitle;
	}
    string HydraEngine::getVNumber() const
    {
        stringstream version;
        version << AutoVersion::STATUS_SHORT << AutoVersion::MAJOR << "." << AutoVersion::MINOR << "." << AutoVersion::REVISION << "b" << AutoVersion::BUILD;
        return version.str();
    }
	SDL_Renderer* HydraEngine::getRenderer() const
	{
		return renderer;
	}
};
