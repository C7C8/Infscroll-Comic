#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_thread.h>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

#include "../version.h"
#include "Logger.h"
#include "Timer.h"
#include "hmath.h"
#include "Sprite.h"

using std::string;
using std::stringstream;

namespace Hydra
{
	class HydraEngine
	{
	public:
		static HydraEngine* getInstance();                              //!< Returns pointer to instance of HydraEngine
		void shutdown();                                                //!< Automatically shuts down all Engine and SDL2 components
		void update();                                                  //!< Has no current function.
		bool init();                                                    //!< Automatically initializes all Engine and SDL2 components.

		//Getters and setters
		void setWSize(Uint16 newXSize = 800, Uint16 newYSize = 600);    //!< Sets the window size to the designated size
		void setWTitle(string newTitle);                                //!< Sets the window title to the designated title

		Uint16 getWXSize() const;
		Uint16 getWYSize() const;
		string getWTitle() const;
		string getVNumber() const;                                      //!< Returns a string containing the version number information
		SDL_Renderer* getRenderer() const;
	private:
	    //Core engine members
	    Logger* systemLog;                                              //!< Logger used for internal engine purposes

		//Singleton stuff
		static HydraEngine* instance;
		HydraEngine();
		~HydraEngine();

		//Window & core graphics stuff
		int wYSize;
		int wXSize;
		SDL_Window* window;
		SDL_Renderer* renderer;
		string wTitle;
	};
}
