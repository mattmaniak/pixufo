#include "menus.hpp"
#include "error.hpp"
#include "model.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"

Menu::Menu(Graphics* Graphics): active(true)
{
	model::Button* Play = new model::Button(Graphics, "play", 0);
	Buttons.push_back(Play);

	model::Button* Quit = new model::Button(Graphics, "quit", 1);
	Buttons.push_back(Quit);

	for(size_t idx = 0; idx < Buttons.size(); idx++)
	{
		if(!Buttons[idx]->initialized)
		{
			error::show_box("Can't initialze the menu button with index: "
			                + idx);

			initialized = false;
			return;
		}
	}
	initialized = true;
}

bool Menu::launch(Graphics* Graphics, Keyboard* Keyboard)
{
	current_button_index = 0;
	max_button_index     = 1;

	while(active)
	{
		if(!Buttons[0]->render(Graphics, current_button_index))
		{
			return false;
		}
		if(!Buttons[1]->render(Graphics, current_button_index))
		{
			return false;
		}
		SDL_RenderPresent(Graphics->Renderer);

		if(!Keyboard->handle_menu(this))
		{
			return false;
		}

		if(SDL_RenderClear(Graphics->Renderer) != SDL2_SUCCESS)
		{
			error::show_box("Can't clean the renderer in the menu.");
			return false;
		}
	}
	return true;
}

Menu::~Menu()
{
	for(size_t idx = 0; idx < Buttons.size(); idx++)
	{
		delete Buttons[idx];
	}
}
