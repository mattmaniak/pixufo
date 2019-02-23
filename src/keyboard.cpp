#include "keyboard.hpp"
#include "menu.hpp"
#include "graphics.hpp"
#include "level.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

void Keyboard::count_keys()
{
	pressed_keys_amount = 0;

	if(keys[SDL_SCANCODE_UP])
	{
		pressed_keys_amount++;
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		pressed_keys_amount++;
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		pressed_keys_amount++;
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		pressed_keys_amount++;
	}
}

bool Keyboard::move_player(Level* Level, Menu* Menu, Graphics* Graphics)
{
	std::size_t slowdowns_amount = 0;

	SDL_PollEvent(&Event);
	switch(Event.type)
	{
		case SDL_QUIT:
		return false;
	}
	count_keys();

	if(pressed_keys_amount == 2)
	{
		Level->Ufo->step /= std::sqrt(2.0f);
	}

	if(keys[SDL_SCANCODE_UP])
	{
		Level->Ufo->Slowdowns[vertical]->activate(Graphics, Level->Ufo, up);
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		Level->Ufo->Slowdowns[vertical]->activate(Graphics, Level->Ufo, down);
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		Level->Ufo->Slowdowns[horizontal]->activate(Graphics, Level->Ufo, left);
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		Level->Ufo->Slowdowns[horizontal]->activate(Graphics, Level->Ufo, right);
	}
	if(keys[SDL_SCANCODE_ESCAPE])
	{
		Menu->mode = Menu->pause_enabled;
	}
	Level->Ufo->Slowdowns[vertical]->fly(Level->Ufo, Graphics);
	Level->Ufo->Slowdowns[horizontal]->fly(Level->Ufo, Graphics);

	return true;
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
		break;

		// TODO: DELAY/FADER.
		// case SDLK_ESCAPE:
		// Menu->mode = Menu->all_disabled;
	}
	return true;
}
