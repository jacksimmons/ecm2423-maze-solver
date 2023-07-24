#include "Tilemap.hpp"
#include "TextureManager.hpp"

int level1[20][20] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};


Tilemap::Tilemap()
{
	mTexDirt = TextureManager::LoadTexture("../sprites/dirt.png");
	mTexGrass = TextureManager::LoadTexture("../sprites/grass.png");
	mTexWater = TextureManager::LoadTexture("../sprites/water.png");

	LoadTilemap(level1);

	mSrcRect.x = mDestRect.x = 0;
	mSrcRect.y = mDestRect.y = 0;
	mSrcRect.w = mDestRect.w = 32;
	mSrcRect.h = mDestRect.h = 32;
}


Tilemap::~Tilemap()
{
	SDL_DestroyTexture(mTexDirt);
	SDL_DestroyTexture(mTexGrass);
	SDL_DestroyTexture(mTexWater);
}


void Tilemap::LoadTilemap(int arr[20][20])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			mTiles[i][j] = arr[i][j];
		}
	}
}


void Tilemap::DrawTilemap()
{
	int type = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			type = mTiles[i][j];

			mDestRect.x = j * 32;
			mDestRect.y = i * 32;
			
			switch (type)
			{
			case 0:
				TextureManager::Draw(mTexWater, mSrcRect, mDestRect);
				break;
			case 1:
				TextureManager::Draw(mTexDirt, mSrcRect, mDestRect);
				break;
			case 2:
				TextureManager::Draw(mTexGrass, mSrcRect, mDestRect);
				break;
			}
		}
	}
}