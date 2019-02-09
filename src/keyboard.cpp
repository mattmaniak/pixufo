#include "keyboard.hpp"
#include "menu.hpp"
#include "rendering.hpp"
#include "level.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::move_player(Level* Level, Menu* Menu)
{
	SDL_PollEvent(&Event);
	count_keys();

	if(keys_amount == 2)
	{
		Level->Ufo->step /= std::sqrt(2.0f);
	}

	switch(Event.type)
	{
		case SDL_QUIT:
		return false;

		case SDL_KEYDOWN:
		switch(Event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
			Menu->mode = Menu->pause_enabled;
			break;
		}
		case SDL_KEYUP:
		if(keys[SDL_SCANCODE_UP])
		{
			Level->Ufo->pos_y -= Level->Ufo->step;

			Level->Player_levitation->current_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->up;

			levitate_diagonally(Level, SDL_SCANCODE_UP);
			last_key = SDL_SCANCODE_UP;
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			Level->Ufo->pos_y += Level->Ufo->step;

			Level->Player_levitation->current_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->down;

			levitate_diagonally(Level, SDL_SCANCODE_DOWN);
			last_key = SDL_SCANCODE_DOWN;
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			Level->Ufo->pos_x -= Level->Ufo->step;

			Level->Player_levitation->current_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->left;

			last_key = SDL_SCANCODE_LEFT;
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			Level->Ufo->pos_x += Level->Ufo->step;

			Level->Player_levitation->current_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->right;

			last_key = SDL_SCANCODE_RIGHT;
		}
	}
	Level->check_player_pos();
	Level->Player_levitation->set_direction(Level->Ufo);

	return true;
}

void Keyboard::levitate_diagonally(Level* Level, SDL_Scancode key)
{
	/* Saving the last key gives a small time window when the player can release
	the keys in different moments. */
	if(key == SDL_SCANCODE_UP)
	{
		if(last_key == SDL_SCANCODE_LEFT)
		{
			Level->Player_levitation->last_direction =
			Level->Player_levitation->left_up;
		}
		else if(last_key == SDL_SCANCODE_RIGHT)
		{
			Level->Player_levitation->last_direction =
			Level->Player_levitation->right_up;
		}
	}
	else if(key == SDL_SCANCODE_DOWN)
	{
		if(last_key == SDL_SCANCODE_LEFT)
		{
			Level->Player_levitation->last_direction =
			Level->Player_levitation->left_down;
		}
		else if(last_key == SDL_SCANCODE_RIGHT)
		{
			Level->Player_levitation->last_direction =
			Level->Player_levitation->right_down;
		}
	}
}

void Keyboard::count_keys()
{
	keys_amount = 0;

	if(keys[SDL_SCANCODE_UP])
	{
		keys_amount++;
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		keys_amount++;
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		keys_amount++;
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		keys_amount++;
	}
}

bool Keyboard::menu(Menu* Menu)
{
	SDL_PollEvent(&Event);

	switch(Event.type)
	{
		case SDL_QUIT:
		return false;

		case SDL_KEYDOWN:
		switch(Event.key.keysym.sym)
		{
			case SDLK_UP:
			if(Menu->current_button_idx > 0)
			{
				Menu->current_button_idx--;
			}
			break;

			case SDLK_DOWN:
			if(Menu->current_button_idx < Menu->max_button_idx)
			{
				Menu->current_button_idx++;
			}
			break;

			case SDLK_RETURN:
			switch(Menu->current_button_idx)
			{
				case 0:
				Menu->mode = Menu->all_disabled;
				break;

				case 1:
				return false;
			}
		}
	}
	return true;
}

bool Keyboard::pause(Menu* Menu)
{
	SDL_PollEvent(&Event);

	switch(Event.type)
	{
		case SDL_QUIT:
		return false;
	}
	switch(Event.key.keysym.sym)
	{
		case SDLK_UP:
		if(Menu->current_button_idx > 0)
		{
			Menu->current_button_idx--;
		}
		break;

		case SDLK_DOWN:
		if(Menu->current_button_idx < Menu->max_button_idx)
		{
			Menu->current_button_idx++;
		}
		break;

		case SDLK_RETURN:
		switch(Menu->current_button_idx)
		{
			case 0:
			Menu->mode = Menu->all_disabled;
			break;

			case 1:
			Menu->mode = Menu->primary_enabled;
		}
	}
	return true;
}
