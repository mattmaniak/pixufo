#include "keyboard.hpp"
#include "menu.hpp"

bool Keyboard::menu(Menus& Menus)
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
			if(Menus.selected_button_idx > 0)
			{
				Menus.selected_button_idx--;
			}
			break;

			case SDLK_DOWN:
			if(Menus.selected_button_idx < (Menus.Buttons.size() - 1))
			{
				Menus.selected_button_idx++;
			}
			break;

			case SDLK_RETURN:
			switch(Menus.selected_button_idx)
			{
				case 0:
				Menus.mode = Menus.all_disabled;
				break;

				case 1:
				return false;
			}
		}
	}
	return true;
}

bool Keyboard::pause(Menus& Menus)
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
		if(Menus.selected_button_idx > 0)
		{
			Menus.selected_button_idx--;
		}
		break;

		case SDLK_DOWN:
		if(Menus.selected_button_idx < (Menus.Buttons.size() - 1))
		{
			Menus.selected_button_idx++;
		}
		break;

		case SDLK_RETURN:
		switch(Menus.selected_button_idx)
		{
			case 0:
			Menus.mode = Menus.all_disabled;
			break;

			case 1:
			Menus.mode = Menus.primary_enabled;
		}
		// TODO: DELAY/FADER.
		// case SDLK_ESCAPE:
		// Menus.mode = Menus.all_disabled;
	}
	return true;
}
