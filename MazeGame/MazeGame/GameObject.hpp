#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Game.hpp"


class GameObject {
private:
	int mPosX, mPosY;
	SDL_Texture *mTexture;
	SDL_Rect mSrcRect, mDestRect;
public:
	GameObject(const char *textureSheetFName, int x, int y);
	~GameObject();

	void update();
	void render();
};

#endif