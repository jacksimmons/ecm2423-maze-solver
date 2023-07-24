#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"


class Game {
private:
	int cnt = 0;
	bool mIsRunning;
	SDL_Window *mWindow;
public:
	Game(const char *title, int posX, int posY, int w, int h, bool fullscreen);
	~Game();
	void init(const char *title, int posX, int posY, int w, int h, bool fullscreen);

	void handleEvents();
	void update();
	void render();

	static SDL_Renderer *sRenderer;

	bool getIsRunning() {
		return mIsRunning;
	}
};

#endif