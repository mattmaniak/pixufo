#include "keyboard.hpp"
#include "menu.hpp"
#include "graphics.hpp"
#include "level.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::move_player(Player* Ufo, Menu* Menu, Graphics* Graphics)
{
	SDL_PollEvent(&Event);
	switch(Event.type)
	{
		case SDL_QUIT:
		return false;
	}

	if(keys[SDL_SCANCODE_UP])
	{
		Ufo->Slowdowns[vertical]->activate(Graphics, up);
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		Ufo->Slowdowns[vertical]->activate(Graphics, down);
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		Ufo->Slowdowns[horizontal]->activate(Graphics, left);
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		Ufo->Slowdowns[horizontal]->activate(Graphics, right);
	}
	if(keys[SDL_SCANCODE_ESCAPE])
	{
		Menu->mode = Menu->pause_enabled;
	}
	Ufo->Slowdowns[vertical]->fly(Ufo, Graphics);
	Ufo->Slowdowns[horizontal]->fly(Ufo, Graphics);

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
