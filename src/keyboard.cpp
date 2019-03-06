#include "keyboard.hpp"
#include "menu.hpp"

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
			if(Menu.selected_button_idx < (Menu.Buttons.size() - 1))
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
		if(Menu.selected_button_idx < (Menu.Buttons.size() - 1))
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
