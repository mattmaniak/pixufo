#include "keyboard.hpp"
#include "menus.hpp"
#include "pause.hpp"
#include "graphics.hpp"
#include "level.hpp"
#include "models.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

}

bool Keyboard::handle_ingame(Graphics* Graphics, Model_player* Player,
                             bool* pause_active, Level* Level)
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
	if(keys_amount == 2)
	{
		Player->step /= std::sqrt(2.0f);
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
			// The player can't go above the level.
			if((Player->pos_y) > -((Level->height + Player->Geometry.h) / 2))
			{
				Player->pos_y -= Player->step;
			}
			else // Don't slow down near the border when two keys are pressed.
			{
				Player->pos_y = (Level->height - Player->Geometry.h) / 2;
				// Player->step *= std::sqrt(2.0f);
			}
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			// The player can't go below the level.
			if(Player->pos_y < (Level->height / 2))
			{
				Player->pos_y += Player->step;
			}
			else // Don't slow down near the border when two keys are pressed.
			{
				Player->pos_y = Level->height / 2;
				// Player->step *= std::sqrt(2.0f);
			}
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			// The player can't go behind the right side of the level.
			if(Player->pos_x > -((Level->width + Player->Geometry.w) / 2))
			{
				Player->pos_x -= Player->step;
			}
			else // Don't slow down near the border when two keys are pressed.
			{
				Player->pos_x = (Level->width - Player->Geometry.w) / 2;
				// Player->step *= std::sqrt(2.0f);
			}
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			// The player can't go behind the left side of the level.
			if(Player->pos_x < (Level->width / 2))
			{
				Player->pos_x += Player->step;
			}
			else // Don't slow down near the border when two keys are pressed.
			{
				Player->pos_x = Level->width / 2;
				// Player->step *= std::sqrt(2.0f);
			}
		}
	}
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
