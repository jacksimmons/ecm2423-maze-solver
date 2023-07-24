#include <memory>

#include <SDL.h>

#include "Game.hpp"


int main(int argc, char **argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameLength;

	std::unique_ptr<Game> game = std::make_unique<Game>("BirchEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);

	while (game->getIsRunning())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameLength = SDL_GetTicks() - frameStart;

		// Ensures every frame is the same length
		if (frameDelay > frameLength)
		{
			SDL_Delay(frameDelay - frameLength);
		}
	}

	game->~Game();

	return 0;
}