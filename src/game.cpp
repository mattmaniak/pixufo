#include "model.hpp"
#include "game.hpp"

Game::Game()
{
	running = true;
	menu    = true;
	pause   = false;
}

Game::~Game()
{
	SDL_Quit();
}

void Game::handle_keyboard(Model_player* Player)
{
	const Uint8* key = SDL_GetKeyboardState(nullptr);
	Uint8        pressed_keys_amount = 0;

	SDL_PollEvent(&event);

	for(Uint8 index = 0; index < std::numeric_limits<Uint8>::max(); index++)
	{
		if(key[index] == 1)
		{
			pressed_keys_amount++;
		}
	}
	if(pressed_keys_amount > 1)
	{
		Player->step = Player->step / std::sqrt(2.0f);
	}

	switch(event.type)
	{
		case SDL_QUIT:
		running = false;
		return;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		if(key[SDL_SCANCODE_UP])
		{
			// if(Player->pos_y >= Player->step)
			// {
				Player->pos_y -= Player->step;
			// }
		}
		if(key[SDL_SCANCODE_DOWN])
		{
			// if((Player->pos_y + Player->Geometry.h + Player->step) <= Player->max_y)
			// {
				Player->pos_y += Player->step;
			// }
		}
		if(key[SDL_SCANCODE_LEFT])
		{
			// if(Player->pos_x >= Player->step)
			// {
				Player->pos_x -= Player->step;
			// }
		}
		if(key[SDL_SCANCODE_RIGHT])
		{
			// if((Player->pos_x + Player->Geometry.w + Player->step) <= Player->max_x)
			// {
				Player->pos_x += Player->step;
			// }
		}
		if(key[SDL_SCANCODE_ESCAPE])
		{
			pause = !pause;
		}
	}
}
