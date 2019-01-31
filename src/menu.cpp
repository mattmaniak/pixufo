#include "menu.hpp"
#include "error.hpp"
#include "model.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"

Menu::Menu(): mode(primary_enabled)
{

}

bool Menu::primary(Graphics* Graphics, Keyboard* Keyboard)
{
	model::Button Play(Graphics, "play", 0);
	if(!Play.initialized)
	{
		return false;
	}
	Buttons.push_back(&Play);

	model::Button Quit(Graphics, "quit", 1);
	if(!Quit.initialized)
	{
		return false;
	}
	Buttons.push_back(&Quit);

	current_button_index = 0;
	max_button_index     = 1;

	while(mode == primary_enabled)
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

bool Menu::pause(Graphics* Graphics, Keyboard* Keyboard)
{
	model::Button Continue(Graphics, "continue", 0);
	if(!Continue.initialized)
	{
		error::show_box("Can't initialize the continue button.");
		return false;
	}
	Buttons.push_back(&Continue);

	model::Button Main_menu(Graphics, "main_menu", 1);
	if(!Main_menu.initialized)
	{
		error::show_box("Can't initialize the main menu button.");
		return false;
	}
	Buttons.push_back(&Main_menu);

	current_button_index = 0;
	max_button_index     = 1;

	while(mode == pause_enabled)
	{
		if(SDL_RenderClear(Graphics->Renderer) != SDL2_SUCCESS)
		{
			error::show_box("Can't clean the renderer in the pause menu.");
			return false;
		}
		if(!Continue.render(Graphics, current_button_index))
		{
			return false;
		}
		if(!Main_menu.render(Graphics, current_button_index))
		{
			return false;
		}
		SDL_RenderPresent(Graphics->Renderer);

		if(!Keyboard->handle_pause(this))
		{
			return false;
		}
	}
	return true;
}
