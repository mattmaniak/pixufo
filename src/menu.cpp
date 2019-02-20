#include "menu.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"
#include "level.hpp"

Menu::Menu(): mode(primary_enabled)
{

}

bool Menu::primary(Graphics* Graphics, Keyboard* Keyboard)
{
	// Space_bg = new Background(Graphics, "planet_menu");

	Space_bg = new Background(Graphics, "background_primary_menu");
	if(!Space_bg->initialized)
	{
		return false;
	}

	Button Play(Graphics, "button_play", 0);
	if(!Play.initialized)
	{
		return false;
	}
	Buttons.push_back(&Play);

	Button Quit(Graphics, "button_quit", 1);
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
		Graphics->start_fps_count();

		if(!Graphics->render_primary_menu(this))
		{
			Buttons.clear();
			delete Space_bg;
			return false;
		}
		if(!Keyboard->menu(this))
		{
			Buttons.clear();
			delete Space_bg;
			return false;
		}
		Graphics->count_fps();
	}
	Buttons.clear();
	delete Space_bg;

	return true;
}

bool Menu::pause(Graphics* Graphics, Keyboard* Keyboard, Level* Level)
{
	Button Continue(Graphics, "button_continue", 0);
	if(!Continue.initialized)
	{
		return false;
	}
	Buttons.push_back(&Continue);

	Button Main_menu(Graphics, "button_main_menu", 1);
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
		if(!Graphics->render_pause_menu(this, Level))
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
