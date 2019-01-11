#include "sdlwrap.hpp"
#include "game.hpp"

Game::Game()
{

}

Game::~Game()
{
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
