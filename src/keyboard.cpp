#include "keyboard.hpp"
#include "menus.hpp"
#include "pause.hpp"
#include "models.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::handle_ingame(Model_player* Player, bool* pause_active)
{
	SDL_PollEvent(&event);

	keys_amount = 0;

	// TODO
	for(Uint8 index = 0; index < std::numeric_limits<Uint8>::max(); index++)
	{
		if(keys[index])
		{
			keys_amount++;
		}
	}
	if(keys_amount == 2)
	{
		Player->step /= std::sqrt(2.0f);
	}

	switch(event.type)
	{
		case SDL_QUIT:
		return false;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		if(keys[SDL_SCANCODE_UP])
		{
			// if(Player->pos_y >= Player->step)
			// {
				Player->pos_y -= Player->step;
			// }
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			// if((Player->pos_y + Player->Geometry.h + Player->step) <= Player->max_y)
			// {
				Player->pos_y += Player->step;
			// }
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			// if(Player->pos_x >= Player->step)
			// {
				Player->pos_x -= Player->step;
			// }
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			// if((Player->pos_x + Player->Geometry.w + Player->step) <= Player->max_x)
			// {
				Player->pos_x += Player->step;
			// }
		}
		if(keys[SDL_SCANCODE_ESCAPE])
		{
			*pause_active = !*pause_active;
		}
	}
	return true;
}

bool Keyboard::handle_menu(Menu* Menu)
{
	SDL_PollEvent(&event);

	if(keys[SDL_SCANCODE_UP] && (Menu->current_button_index > 0))
	{
		Menu->current_button_index--;
	}
	else if(keys[SDL_SCANCODE_DOWN]
	&& (Menu->current_button_index < Menu->max_button_index))
	{
		Menu->current_button_index++;
	}
	else if(keys[SDL_SCANCODE_RETURN])
	{
		switch(Menu->current_button_index)
		{
			case 0:
			Menu->active = false;
			break;

			case 1:
			return false;
		}
	}
	return true;
}

bool Keyboard::handle_pause(Menu* Menu, Pause* Pause)
{
	SDL_PollEvent(&event);

	if(keys[SDL_SCANCODE_UP] && (Pause->current_button_index > 0))
	{
		Pause->current_button_index--;
	}
	else if(keys[SDL_SCANCODE_DOWN]
	&& (Pause->current_button_index < Pause->max_button_index))
	{
		Pause->current_button_index++;
	}
	else if(keys[SDL_SCANCODE_RETURN])
	{
		switch(Pause->current_button_index)
		{
			case 1:
			Menu->active = true;
		}
		Pause->active = false;
	}
	return true;
}
