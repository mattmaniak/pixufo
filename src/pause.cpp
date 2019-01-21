#include "pause.hpp"
#include "menus.hpp"
#include "models.hpp"
#include "keyboard.hpp"
#include "graphics.hpp"

Pause::Pause(): active(false)
{

}

bool Pause::launch(Graphics* Graphics, Keyboard* Keyboard, Menu* Menu)
{
	Model_button Continue(Graphics, "continue", 0);
	Model_button Main_menu(Graphics, "main_menu", 1);

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

	while(active)
	{
		if(SDL_RenderClear(Graphics->Renderer) != SUCCESS)
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		Continue.render(Graphics, current_button_index);
		Main_menu.render(Graphics, current_button_index);
		SDL_RenderPresent(Graphics->Renderer);

		Keyboard->handle_pause(Menu, this);
	}
	return true;
}
