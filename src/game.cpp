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
	// SDL_DestroyRenderer(renderer);
	// SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::_error(const std::string message)
{
	std::cerr << message << std::endl;
	quit();
	exit(1);
}
