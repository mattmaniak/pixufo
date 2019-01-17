#include "model.hpp"
#include "game.hpp"

Game::Game()
{
	running = true;
}

Game::~Game()
{
	SDL_Quit();
	running = false;
}

void Game::handle_keyboard(Model* Player, const Uint8* key)
{
	switch(event.type)
	{
		case SDL_QUIT:
		running = false;
		return;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		if(key[SDL_SCANCODE_UP])
		{
			if(Player->y >= Player->step)
			{
				Player->y -= Player->step;
			}
		}
		if(key[SDL_SCANCODE_DOWN])
		{
			if((Player->y + Player->Geometry.h + Player->step) <= Player->max_y)
			{
				Player->y += Player->step;
			}
		}
		if(key[SDL_SCANCODE_LEFT])
		{
			if(Player->x >= Player->step)
			{
				Player->x -= Player->step;
			}
		}
		if(key[SDL_SCANCODE_RIGHT])
		{
			if((Player->x + Player->Geometry.w + Player->step) <= Player->max_y)
			{
				Player->x += Player->step;
			}
		}
		if(key[SDL_SCANCODE_ESCAPE])
		{
			running = false;
		}
	}
}
