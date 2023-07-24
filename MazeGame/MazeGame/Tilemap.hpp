#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "Game.hpp"


class Tilemap {
private:
	SDL_Rect mSrcRect, mDestRect;
	SDL_Texture *mTexDirt, *mTexGrass, *mTexWater;
	int mTiles[20][20];
public:
	Tilemap();
	~Tilemap();

	void LoadTilemap(int arr[20][20]);
	void DrawTilemap();
};
#endif