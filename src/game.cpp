#include "sdlwrap.hpp"
#include "game.hpp"

Game::Game()
{
	running = true;
}

Game::~Game()
{
	running = false;
	quit();
}

void Game::loop()
{
	// TODO
}

void Game::quit()
{
	SDL_Quit();
}
