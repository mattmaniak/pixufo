#include "menus.hpp"
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

	while(active)
	{
		Play.render(Graphics, current_button_index);
		Quit.render(Graphics, current_button_index);
		SDL_RenderPresent(Graphics->Renderer);

		if(!Keyboard->handle_menu(this))
		{
			return false;
		}

		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
	}
	return true;
}
