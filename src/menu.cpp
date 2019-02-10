#include "menu.hpp"
#include "error.hpp"
#include "button.hpp"
#include "rendering.hpp"
#include "keyboard.hpp"

Menu::Menu(): mode(primary_enabled)
{

}

bool Menu::primary(Rendering* Rendering, Keyboard* Keyboard)
{
	Button Play(Rendering, "play", 0);
	if(!Play.initialized)
	{
		return false;
	}
	Buttons.push_back(&Play);

	Button Quit(Rendering, "quit", 1);
	if(!Quit.initialized)
	{
		Buttons.clear();
		return false;
	}
	Buttons.push_back(&Quit);

	max_button_idx      = 1;
	selected_button_idx = 0;

	while(mode == primary_enabled)
	{
		if(!Rendering->render_primary_menu(this))
		{
			Buttons.clear();
			return false;
		}
		if(!Keyboard->menu(this))
		{
			Buttons.clear();
			return false;
		}
	}
	Buttons.clear();
	return true;
}

bool Menu::pause(Rendering* Rendering, Keyboard* Keyboard)
{
	Button Continue(Rendering, "continue", 0);
	if(!Continue.initialized)
	{
		return false;
	}
	Buttons.push_back(&Continue);

	Button Main_menu(Rendering, "main_menu", 1);
	if(!Main_menu.initialized)
	{
		Buttons.clear();
		return false;
	}
	Buttons.push_back(&Main_menu);

	max_button_idx      = 1;
	selected_button_idx = 0;

	while(mode == pause_enabled)
	{
		if(!Rendering->render_pause_menu(this))
		{
			Buttons.clear();
			return false;
		}
		if(!Keyboard->pause(this))
		{
			Buttons.clear();
			return false;
		}
	}
	Buttons.clear();

	return true;
}
