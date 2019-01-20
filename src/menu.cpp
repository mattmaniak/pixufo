#include "graphics.hpp"
#include "model.hpp"
#include "game.hpp"
#include "menu.hpp"

Button::Button(Graphics* Graphics, const std::string name, const int idx)
: Model_basic(Graphics, name), index(idx)
{

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

bool Menu::primal(Game* Game, Graphics* Graphics)
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

	while(Game->menu)
	{
		Play.render(Graphics, this);
		Quit.render(Graphics, this);
		SDL_RenderPresent(Graphics->Renderer);

		handle_keyboard(Game);

		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		if(!Game->running)
		{
			return false;
		}
	}
	return true;
}

void Menu::handle_keyboard(Game* Game)
{
	const Uint8* key = SDL_GetKeyboardState(nullptr);

	SDL_PollEvent(&Game->event);

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
		if(Game->menu)
		{
			switch(current_button_index)
			{
				case 0:
				Game->menu = false;
				break;

				case 1:
				Game->running = false;
			}
		}
		else if(Game->pause)
		{
			switch(current_button_index)
			{
				case 1:
				Game->menu = true;
			}
			Game->pause = false;
		}
	}
}

bool Menu::pause(Game* Game, Graphics* Graphics)
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

	while(Game->pause)
	{
		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		Continue.render(Graphics, this);
		Main_menu.render(Graphics, this);
		SDL_RenderPresent(Graphics->Renderer);

		handle_keyboard(Game);
	}
	return true;
}

bool Menu::fader(Graphics* Graphics)
{
	Uint32 fader_time = 500;
	Uint32 start_time = SDL_GetTicks();

	while((SDL_GetTicks() - start_time) < fader_time)
	{
		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		// Continue.render(Graphics, this);
		// Main_menu.render(Graphics, this);
		SDL_RenderPresent(Graphics->Renderer);
	}
	return true;
}
