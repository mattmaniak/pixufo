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

			Level->Ufo->Slowdown->current_time = SDL_GetTicks();
			Level->Ufo->Slowdown->last_direction = Level->Ufo->Slowdown->up;

			levitate_diagonally(Level, SDL_SCANCODE_UP);
			last_key = SDL_SCANCODE_UP;
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			Level->Ufo->pos_y += Level->Ufo->step;

			Level->Ufo->Slowdown->current_time = SDL_GetTicks();
			Level->Ufo->Slowdown->last_direction = Level->Ufo->Slowdown->down;

			levitate_diagonally(Level, SDL_SCANCODE_DOWN);
			last_key = SDL_SCANCODE_DOWN;
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			Level->Ufo->pos_x -= Level->Ufo->step;

			Level->Ufo->Slowdown->current_time = SDL_GetTicks();
			Level->Ufo->Slowdown->last_direction = Level->Ufo->Slowdown->left;

			last_key = SDL_SCANCODE_LEFT;
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			Level->Ufo->pos_x += Level->Ufo->step;

			Level->Ufo->Slowdown->current_time = SDL_GetTicks();
			Level->Ufo->Slowdown->last_direction = Level->Ufo->Slowdown->right;

			last_key = SDL_SCANCODE_RIGHT;
		}
	}
	Level->check_player_pos();
	Level->Ufo->Slowdown->set_direction(Level->Ufo);

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
			Level->Ufo->Slowdown->last_direction =
			Level->Ufo->Slowdown->left_up;
		}
		else if(last_key == SDL_SCANCODE_RIGHT)
		{
			Level->Ufo->Slowdown->last_direction =
			Level->Ufo->Slowdown->right_up;
		}
	}
	else if(key == SDL_SCANCODE_DOWN)
	{
		if(last_key == SDL_SCANCODE_LEFT)
		{
			Level->Ufo->Slowdown->last_direction =
			Level->Ufo->Slowdown->left_down;
		}
		else if(last_key == SDL_SCANCODE_RIGHT)
		{
			Level->Ufo->Slowdown->last_direction =
			Level->Ufo->Slowdown->right_down;
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
			if(Menu->selected_button_idx > 0)
			{
				Menu->selected_button_idx--;
			}
			break;

			case SDLK_DOWN:
			if(Menu->selected_button_idx < Menu->max_button_idx)
			{
				Menu->selected_button_idx++;
			}
			break;

			case SDLK_RETURN:
			switch(Menu->selected_button_idx)
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
		if(Menu->selected_button_idx > 0)
		{
			Menu->selected_button_idx--;
		}
		break;

		case SDLK_DOWN:
		if(Menu->selected_button_idx < Menu->max_button_idx)
		{
			Menu->selected_button_idx++;
		}
		break;

		case SDLK_RETURN:
		switch(Menu->selected_button_idx)
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
