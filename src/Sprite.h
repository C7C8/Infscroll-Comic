#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

namespace Hydra
{
	class Sprite
	{
	public:
		static SDL_Renderer* renderer; //Hackish way of getting this to work normally for Infscroll-comic purposes.

		Sprite();
		virtual void free();
		void loadFromFile(string path, bool blending = false);
		void setColor (int newR, int newG, int newB);
		void setR(int newR);
		void setG(int newG);
		void setB(int newB);
		int getR();
		int getG();
		int getB();
		int getW();
		int getH();
		void setClipX(int newX);
		void setClipY(int newY);
		void setClipH(int newH);
		void setClipW(int newW);
		void setClip(SDL_Rect newCLip);
	
		int getClipX();
		int getClipY();
		int getClipW();
		int getClipH();
		int getScaleW();
		int getScaleH();
		string getName();
		void setName(string newName);
		void setScaleW(int newW);
		void setScaleH(int newH);
		SDL_Rect getScale();
		void setBlending(bool blend = false);
		void setAlpha(int newAlpha = 0);
		int getAlpha();
		SDL_Texture* getTexture();
		void render(int x, int y, int h = -1, int w = -1);
		void setCenterX(int newX = -1);
		void setCenterY(int newY = -1);
		void setCenter(SDL_Point newPoint);
		void setAngle(double newAngle = 0);
		SDL_Point getCenter();
		double getAngle();
	protected:
		int r;
		int g;
		int b;
		int h;
		int w;
		int alpha;
		double angle;
		SDL_Point center;
		SDL_Rect scale;
		SDL_Rect clip;

		SDL_Texture* texture;
		string name; //Used to identify this particular comic (Infscroller-comic)
	};
};
