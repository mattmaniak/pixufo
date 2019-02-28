#include "keyboard.hpp"
#include "menu.hpp"
#include "graphics.hpp"
#include "player.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::move_player(Player& Ufo, Menu& Menu, Graphics& Graphics)
{
	Ufo.directions_amount = 0;

	SDL_PollEvent(&Event);
	switch(Event.type)
	{
		case SDL_QUIT:
		return false;
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		Ufo.Movements[horizontal]->count_ratio(Graphics, left);
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		Ufo.Movements[horizontal]->count_ratio(Graphics, right);
	}
	if(keys[SDL_SCANCODE_UP])
	{
		Ufo.Movements[vertical]->count_ratio(Graphics, up);
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		Ufo.Movements[vertical]->count_ratio(Graphics, down);
	}
	if(keys[SDL_SCANCODE_ESCAPE])
	{
		Menu.mode = Menu.pause_enabled;
	}

	if((Ufo.horizontal_speed != 0.0f) && (Ufo.vertical_speed != 0.0f))
	{
		Ufo.directions_amount = 2;
	}
	Ufo.Movements[vertical]->move(Graphics, Ufo);
	Ufo.Movements[horizontal]->move(Graphics, Ufo);

	return true;
}

bool Keyboard::menu(Menu& Menu)
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
			if(Menu.selected_button_idx > 0)
			{
				Menu.selected_button_idx--;
			}
			break;

			case SDLK_DOWN:
			if(Menu.selected_button_idx < Menu.max_button_idx)
			{
				Menu.selected_button_idx++;
			}
			break;

			case SDLK_RETURN:
			switch(Menu.selected_button_idx)
			{
				case 0:
				Menu.mode = Menu.all_disabled;
				break;

				case 1:
				return false;
			}
		}
	}
	return true;
}

bool Keyboard::pause(Menu& Menu)
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
		if(Menu.selected_button_idx > 0)
		{
			Menu.selected_button_idx--;
		}
		break;

		case SDLK_DOWN:
		if(Menu.selected_button_idx < Menu.max_button_idx)
		{
			Menu.selected_button_idx++;
		}
		break;

		case SDLK_RETURN:
		switch(Menu.selected_button_idx)
		{
			case 0:
			Menu.mode = Menu.all_disabled;
			break;

			case 1:
			Menu.mode = Menu.primary_enabled;
		}
		break;

		// TODO: DELAY/FADER.
		// case SDLK_ESCAPE:
		// Menu.mode = Menu.all_disabled;
	}
	return true;
}
