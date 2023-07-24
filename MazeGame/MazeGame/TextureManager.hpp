#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "Game.hpp"


class TextureManager {
public:
	static SDL_Texture *LoadTexture(const char *fileName);
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};

#endif