#include "keyboard.hpp"
#include "menus.hpp"
#include "pause.hpp"
#include "graphics.hpp"
#include "level.hpp"
#include "model.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::handle_ingame(Graphics* Graphics, Level* Level, bool* pause_active)
{
	SDL_PollEvent(&Event);
	keys_amount = 0;

	// TODO
	for(Uint8 index = 0; index < std::numeric_limits<Uint8>::max(); index++)
	{
		if(keys[index])
		{
			keys_amount++;
		}
	}
	if(keys_amount >= 2)
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
			*pause_active = true;
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
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			Level->Player->pos_y += Level->Player->step;

			if(Level->Player->pos_y >= (Level->height - Level->Player->count_scale()))
			{
				Level->Player->pos_y = -(Level->Player->Geometry.h - Level->Player->count_scale());
			}
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			Level->Player->pos_x -= Level->Player->step;

			if(Level->Player->pos_x <= -(Level->Player->Geometry.w - Level->Player->count_scale()))
			{
				Level->Player->pos_x = Level->width - Level->Player->count_scale();
			}
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			Level->Player->pos_x += Level->Player->step;

			if(Level->Player->pos_x >= (Level->width - Level->Player->count_scale()))
			{
				Level->Player->pos_x = -(Level->Player->Geometry.w - Level->Player->count_scale());
			}
		}
		// Level->Player->current_levitation_time = SDL_GetTicks();
	}
	Level->Player->count_levitation_time(Graphics);
	return true;
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
				Menu->active = false;
				break;;

				case 1:
				return false;
			}
		}
	}
	return true;
}

bool Keyboard::handle_pause(Menu* Menu, Pause* Pause)
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
		if(Pause->current_button_index > 0)
		{
			Pause->current_button_index--;
		}
		break;

		case SDLK_DOWN:
		if(Pause->current_button_index < Menu->max_button_index)
		{
			Pause->current_button_index++;
		}
		break;

		case SDLK_RETURN:
		switch(Pause->current_button_index)
		{
			case 1:
			Menu->active = true;
		}
		Pause->active = false;
	}
	return true;
}
