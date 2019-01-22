#include "menus.hpp"
#include "error.hpp"
#include "models.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"

Menu::Menu(): active(true)
{

}

bool Menu::launch(Graphics* Graphics, Keyboard* Keyboard)
{
	Model_button Play(Graphics, "play", 0);
	Model_button Quit(Graphics, "quit", 1);

	if(!Play.initialized)
	{
		error::show_box("Can't initialize the play button.");
		return false;
	}
	if(!Quit.initialized)
	{
		error::show_box("Can't initialize the quit button.");
		return false;
	}
	current_button_index = 0;
	max_button_index     = 1;

	while(active)
	{
		if(!Play.render(Graphics, current_button_index))
		{
			return false;
		}
		if(!Quit.render(Graphics, current_button_index))
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
