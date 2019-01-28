#include "pause.hpp"
#include "error.hpp"
#include "menus.hpp"
#include "model.hpp"
#include "keyboard.hpp"
#include "graphics.hpp"

Pause::Pause(): active(false)
{

}

bool Pause::launch(Graphics* Graphics, Keyboard* Keyboard, Menu* Menu)
{
	model::Button Continue(Graphics, "continue", 0);
	model::Button Main_menu(Graphics, "main_menu", 1);

	if(!Continue.initialized)
	{
		error::show_box("Can't initialize the continue button.");
		return false;
	}
	if(!Main_menu.initialized)
	{
		error::show_box("Can't initialize the main menu button.");
		return false;
	}
	current_button_index = 0;
	max_button_index     = 1;

	while(active)
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

		if(!Keyboard->handle_pause(Menu, this))
		{
			return false;
		}
	}
	return true;
}
