#include "keyboard.hpp"
#include "menu.hpp"
#include "rendering.hpp"
#include "level.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Keyboard::Keyboard(): keys(SDL_GetKeyboardState(nullptr))
{

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

bool Keyboard::move_player(Level* Level, Menu* Menu)
{
	unsigned int slowdowns_amount = 0;

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
		SDL_PumpEvents();

		if(keys[SDL_SCANCODE_UP])
		{
			if(!Level->Ufo->Acceleration[down]->active)
			{
				Level->Ufo->Acceleration[down]->activate(down);
			}
			Level->Ufo->pos_y -= Level->Ufo->step;
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			if(!Level->Ufo->Acceleration[up]->active)
			{
				Level->Ufo->Acceleration[up]->activate(up);
			}
			Level->Ufo->pos_y += Level->Ufo->step;

		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			if(!Level->Ufo->Acceleration[right]->active)
			{
				Level->Ufo->Acceleration[right]->activate(right);
			}
			Level->Ufo->pos_x -= Level->Ufo->step;
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			if(!Level->Ufo->Acceleration[left]->active)
			{
				Level->Ufo->Acceleration[left]->activate(left);
			}
			Level->Ufo->pos_x += Level->Ufo->step;
		}
		switch(Event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
			Menu->mode = Menu->pause_enabled;
			break;
		}

		case SDL_KEYUP:
		if(keys[SDL_SCANCODE_UP])
		{
			// Level->Ufo->pos_y -= Level->Ufo->step;
			Level->Ufo->Slowdown[up]->activate(up);
		}
		if(keys[SDL_SCANCODE_DOWN])
		{
			// Level->Ufo->pos_y += Level->Ufo->step;
			Level->Ufo->Slowdown[down]->activate(down);
		}
		if(keys[SDL_SCANCODE_LEFT])
		{
			// Level->Ufo->pos_x -= Level->Ufo->step;
			Level->Ufo->Slowdown[left]->activate(left);
		}
		if(keys[SDL_SCANCODE_RIGHT])
		{
			// Level->Ufo->pos_x += Level->Ufo->step;
			Level->Ufo->Slowdown[right]->activate(right);
		}
	}


	for(std::size_t dir_idx = 0; dir_idx < 4; dir_idx++)
	{
		// if(Level->Ufo->Slowdown[dir_idx]->active)
		// {
		// 	slowdowns_amount++;
		// }
		// if((slowdowns_amount >= 2) // Diagonal speed-ups prevention.
		//    || ((keys_amount >= 1) && (slowdowns_amount >= 1)))
		// {
		// 	Level->Ufo->step /= std::sqrt(2.0f);
		// }
		Level->Ufo->Acceleration[dir_idx]->set_direction(Level->Ufo);
	}


	for(std::size_t dir_idx = 0; dir_idx < 4; dir_idx++)
	{
		if(Level->Ufo->Slowdown[dir_idx]->active)
		{
			slowdowns_amount++;
		}
		if((slowdowns_amount >= 2) // Diagonal speed-ups prevention.
		   || ((keys_amount >= 1) && (slowdowns_amount >= 1)))
		{
			Level->Ufo->step /= std::sqrt(2.0f);
		}
		Level->Ufo->Slowdown[dir_idx]->set_direction(Level->Ufo);
	}
	Level->check_player_pos();

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
		case SDLK_ESCAPE:
		Menu->mode = Menu->all_disabled;
	}
	return true;
}
