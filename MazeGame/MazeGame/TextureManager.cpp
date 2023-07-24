#include "TextureManager.hpp"


// Returns and delegates a pointer to a texture
SDL_Texture *TextureManager::LoadTexture(const char *fileName)
{
	SDL_Surface *tempSurface = IMG_Load(fileName);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::sRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return texture;
}


void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::sRenderer, tex, &src, &dest);
}