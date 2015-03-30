#include "Sprite.h"
using namespace std;

namespace Hydra
{
	SDL_Renderer* Sprite::renderer = nullptr;
	Sprite::Sprite()
{
	texture = NULL;
	h = 0;
	w = 0;
	scale.h = 0;
	scale.y = 0;
	scale.x = 0;
	scale.y = 0;
	r = 255;
	g = 255;
	b = 255;
	alpha = 255;
}
	void Sprite::free()
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	void Sprite::loadFromFile(string path, bool blending)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		cout << "ERROR: " << IMG_GetError() << endl;
		return;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		cout << "ERROR: " << SDL_GetError() << endl;

	cout << "Successfully loaded " << path << ". BLENDING: " << blending << endl;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	scale.w = w;
	scale.h = h;
	clip.x = 0;
	clip.y = 0;
	clip.h = h;
	clip.w = w;
	angle = 0;
	center.x = w / 2;
	center.y = h / 2;
	SDL_SetTextureColorMod(texture, r, g, b);
	setBlending(blending);
	SDL_FreeSurface(surface);
}
	void Sprite::setColor(int newR, int newG, int newB)
{
	r = newR;
	g = newG;
	b = newB;
	SDL_SetTextureColorMod(texture, r, g, b);
}
	void Sprite::setR(int newR)
{
	r = newR;
	SDL_SetTextureColorMod(texture, r, g, b);
}
	void Sprite::setG(int newG)
{
	g = newG;
	SDL_SetTextureColorMod(texture, r, g, b);
}
	void Sprite::setB(int newB)
{
	b = newB;
	SDL_SetTextureColorMod(texture, r, g, b);
}
	int Sprite::getR()
{
	return r;
}
	int Sprite::getG()
{
	return g;
}
	int Sprite::getB()
{
	return b;
}
	int Sprite::getH()
{
	return h;
}
	int Sprite::getW()
{
	return w;
}
	void Sprite::setClipX(int newX)
{
	clip.x = newX;
}
	void Sprite::setClipY(int newY)
{
	clip.y = newY;
}
	void Sprite::setClipH(int newH)
{
	if (clip.h <= 0)
		clip.h = h;
	clip.h = newH;
}
	void Sprite::setClipW(int newW)
{
	if (newW <= 0)
		newW = w;
	clip.w = newW;
}
	void Sprite::setClip(SDL_Rect newClip)
{
	clip = newClip;
}
	int Sprite::getClipX()
{
	return clip.x;
}
	int Sprite::getClipY()
{
	return clip.y;
}
	int Sprite::getClipW()
{
	return clip.w;
}
	int Sprite::getClipH()
{
	return clip.h;
}
	int Sprite::getScaleW()
{
	return scale.w;
}
	int Sprite::getScaleH()
{
	return scale.h;
}
	SDL_Rect Sprite::getScale()
{
	return scale;
}
	void Sprite::setScaleW(int newW)
{
	if (newW <= 0)
		newW = w;
	scale.w = newW;
}
	void Sprite::setScaleH(int newH)
{
	if (newH <= 0)
		newH = h;
	scale.h = h;
}
	void Sprite::setBlending(bool blend)
{
	if (blend)
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	else
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}
	void Sprite::setAlpha(int newAlpha)
{
	alpha = newAlpha;
	SDL_SetTextureAlphaMod(texture, newAlpha);
}
	int Sprite::getAlpha()
{
	return alpha;
}
	SDL_Texture* Sprite::getTexture()
{
	return texture;
}
	void Sprite::render(int x, int y, int h, int w)
{
	scale.x = x;
	scale.y = y;
	if (h != -1)
		scale.h = h;
	if (w != -1)
		scale.w = w;

	SDL_RenderCopyEx(renderer, texture, &clip, &scale, angle, &center, SDL_FLIP_NONE);
	return;
}
	void Sprite::setCenterX(int newX)
{
	if (newX >= 0)
		center.x = newX;
	else
		center.x = w / 2;
}
	void Sprite::setCenterY(int newY)
{
	if (newY >= 0)
		center.y = newY;
	else
		center.y = h / 2;
}
	void Sprite::setCenter(SDL_Point newPoint)
{
	center = newPoint;
}
	void Sprite::setAngle(double newAngle)
{
	angle = newAngle;
}
	SDL_Point Sprite::getCenter()
{
	return center;
}
	double Sprite::getAngle()
{
	return angle;
}
	string Sprite::getName()
	{
		return name;
	}
	void Sprite::setName(string newName)
	{
		name = newName;
	}
};
