#include "GameObject.hpp"
#include "TextureManager.hpp"


GameObject::GameObject(const char *textureSheetFName, int x, int y)
{
	mTexture = TextureManager::LoadTexture(textureSheetFName);
	mPosX = x; mPosY = y;
}


GameObject::~GameObject()
{
	SDL_DestroyTexture(mTexture);
}


void GameObject::update()
{
	mPosX++;
	mPosY++;

	mSrcRect.x = 0;
	mSrcRect.y = 0;
	mSrcRect.w = 32;
	mSrcRect.h = 32;

	mDestRect.x = mPosX;
	mDestRect.y = mPosY;
	mDestRect.w = mSrcRect.w * 2;
	mDestRect.h = mSrcRect.h * 2;
}


void GameObject::render()
{
	SDL_RenderCopy(Game::sRenderer, mTexture, &mSrcRect, &mDestRect);
}