#include "keyboard.hpp"
#include "menu.hpp"
#include "graphics.hpp"
#include "level.hpp"
#include "model.hpp"
#include "levitation.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::handle_ingame(Level* Level, Menu* Menu)
{
	SDL_PollEvent(&Event);
	count_keys();

	if(keys_amount == 2)
	{
		Level->Player->step /= std::sqrt(2.0f);
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
			Level->Player->pos_y -= Level->Player->step;

			if(Level->Player->pos_y <= -(Level->Player->Geometry.h - Level->Player->count_scale()))
			{
				Level->Player->pos_y = Level->height - Level->Player->count_scale();
			}
			Level->Player->current_levitation_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->up;

			levitate_diagonally(Level, SDL_SCANCODE_UP);
			last_key = SDL_SCANCODE_UP;
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			Level->Player->pos_y += Level->Player->step;

			if(Level->Player->pos_y >= (Level->height - Level->Player->count_scale()))
			{
				Level->Player->pos_y = -(Level->Player->Geometry.h - Level->Player->count_scale());
			}
			Level->Player->current_levitation_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->down;

			levitate_diagonally(Level, SDL_SCANCODE_DOWN);
			last_key = SDL_SCANCODE_DOWN;
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			Level->Player->pos_x -= Level->Player->step;

			if(Level->Player->pos_x <= -(Level->Player->Geometry.w - Level->Player->count_scale()))
			{
				Level->Player->pos_x = Level->width - Level->Player->count_scale();
			}
			Level->Player->current_levitation_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->left;

			last_key = SDL_SCANCODE_LEFT;
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			Level->Player->pos_x += Level->Player->step;

			if(Level->Player->pos_x >= (Level->width - Level->Player->count_scale()))
			{
				Level->Player->pos_x = -(Level->Player->Geometry.w - Level->Player->count_scale());
			}
			Level->Player->current_levitation_time = SDL_GetTicks();
			Level->Player_levitation->last_direction = Level->Player_levitation->right;

			last_key = SDL_SCANCODE_RIGHT;
		}
	}
	Level->Player_levitation->levitate(Level->Player);

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

bool Keyboard::handle_menu(Menu* Menu)
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
			if(Menu->current_button_index > 0)
			{
				Menu->current_button_index--;
			}
			break;

			case SDLK_DOWN:
			if(Menu->current_button_index < Menu->max_button_index)
			{
				Menu->current_button_index++;
			}
			break;

			case SDLK_RETURN:
			switch(Menu->current_button_index)
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

bool Keyboard::handle_pause(Menu* Menu)
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
		if(Menu->current_button_index > 0)
		{
			Menu->current_button_index--;
		}
		break;

		case SDLK_DOWN:
		if(Menu->current_button_index < Menu->max_button_index)
		{
			Menu->current_button_index++;
		}
		break;

		case SDLK_RETURN:
		switch(Menu->current_button_index)
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
