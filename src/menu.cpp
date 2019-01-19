#include "graphics.hpp"
#include "model.hpp"
#include "game.hpp"
#include "menu.hpp"

Button::Button(Graphics* Graphics, const std::string name, const int idx)
: Model(Graphics, name)
{
	index = idx;
}

bool Button::render(Graphics* Graphics, Menu* Menu)
{
	const int actual_button_shift = 64;

	// Centering.
	Geometry.x = (Graphics->Display.w - Geometry.w) / 2;
	Geometry.y = (Graphics->Display.h / 2) + (index * Geometry.h);

	// Shift the selected button.
	if(index == Menu->current_button_index)
	{
		Geometry.x += actual_button_shift;
	}
	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Menu::primal(Game* Pixufo, Graphics* Graphics)
{
	Button Play(Graphics, "play", 0);
	Button Quit(Graphics, "quit", 1);

	if(!Play.initialized)
	{
		std::cerr << "ERROR" << std::endl;
		return false;
	}
	if(!Quit.initialized)
	{
		std::cerr << "ERROR" << std::endl;
		return false;
	}
	current_button_index = 0;
	max_button_index     = 1;

	while(Pixufo->menu)
	{
		Play.render(Graphics, this);
		Quit.render(Graphics, this);
		SDL_RenderPresent(Graphics->Renderer);

		handle_keyboard(Pixufo);

		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		if(!Pixufo->running)
		{
			return false;
		}
	}
	return true;
}

void Menu::handle_keyboard(Game* Pixufo)
{
	const Uint8* key = SDL_GetKeyboardState(nullptr);

	SDL_PollEvent(&Pixufo->event);

	if(key[SDL_SCANCODE_UP] && (current_button_index > 0))
	{
		current_button_index--;
	}
	else if(key[SDL_SCANCODE_DOWN] && (current_button_index < max_button_index))
	{
		current_button_index++;
	}
	else if(key[SDL_SCANCODE_RETURN])
	{
		if(Pixufo->menu)
		{
			if(current_button_index == 0)
			{
				Pixufo->menu = false;
			}
			else if(current_button_index == 1)
			{
				Pixufo->running = false;
			}
		}
		else if(Pixufo->pause)
		{
			if(current_button_index == 1)
			{
				Pixufo->menu = true;
			}
			Pixufo->pause = false;
		}
	}
}

bool Menu::pause(Game* Pixufo, Graphics* Graphics)
{
	Button Continue(Graphics, "continue", 0);
	Button Main_menu(Graphics, "main_menu", 1);

	if(!Continue.initialized)
	{
		std::cerr << "ERROR" << std::endl;
		return false;
	}
	if(!Main_menu.initialized)
	{
		std::cerr << "ERROR" << std::endl;
		return false;
	}
	current_button_index = 0;
	max_button_index     = 1;

	while(Pixufo->pause)
	{
		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		Continue.render(Graphics, this);
		Main_menu.render(Graphics, this);
		SDL_RenderPresent(Graphics->Renderer);

		handle_keyboard(Pixufo);
	}
	return true;
}
