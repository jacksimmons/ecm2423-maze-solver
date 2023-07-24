#include <iostream>

#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Tilemap.hpp"
#include "ECS.hpp"
#include "Components.hpp"

GameObject *player;
GameObject *enemy;
Tilemap *map;

SDL_Renderer *Game::sRenderer = nullptr;
Manager manager;
auto &newPlayer(manager.addEntity());


Game::Game(const char *title, int posX, int posY, int w, int h, bool fullscreen)
{
	mIsRunning = false;
	init(title, posX, posY, w, h, fullscreen);
}


Game::~Game()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(Game::sRenderer);

	player->~GameObject();
	enemy->~GameObject();
	map->~Tilemap();
}


void Game::init(const char *title, int posX, int posY, int w, int h, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Success
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialised." << std::endl;

		mWindow = SDL_CreateWindow(title, posX, posY, w, h, flags);
		// Returns true unless failure
		if (mWindow)
		{
			std::cout << "Window created." << std::endl;
		}

		sRenderer = SDL_CreateRenderer(mWindow, -1, flags);
		// Returns true unless failure
		if (sRenderer)
		{
			std::cout << "Renderer created." << std::endl;
		}

		mIsRunning = true;
	}

	player = new GameObject("../sprites/player.png", 100, 100);
	enemy = new GameObject("../sprites/enemy.png", 500, 0);
	map = new Tilemap();

	newPlayer.addComponent<PositionComponent>();
}


void Game::handleEvents()
{
	SDL_Event sdl_event;
	SDL_PollEvent(&sdl_event);

	switch (sdl_event.type) {
	case SDL_QUIT:
		mIsRunning = false;
		break;
	default:
		break;
	}
}


void Game::update()
{
	player->update();
	enemy->update();

	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().getX()
		<< ", " << newPlayer.getComponent<PositionComponent>().getY() << std::endl;

	std::cout << cnt << std::endl;
}


void Game::render()
{
	SDL_RenderClear(sRenderer);

	map->DrawTilemap();
	player->render();
	enemy->render();

	SDL_RenderPresent(sRenderer);
}