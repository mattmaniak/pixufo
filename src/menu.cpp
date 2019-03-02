#include "menu.hpp"

Menu::Menu(Graphics& Graphics):
Scene(Graphics, "background_primary_menu"), mode(primary_enabled)
{
	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	Select_arrow = new Sprite(Graphics, "planet_orange", 0.0, 0);
	if(!Select_arrow->is_initialized)
	{
		is_initialized = false;
		return;
	}
	is_initialized = true;
}

Menu::~Menu()
{
	if(Select_arrow->is_initialized)
	{
		delete Select_arrow;
	}
}

bool Menu::primary(Graphics& Graphics, Keyboard& Keyboard)
{
	Logo = new Sprite(Graphics, "title", 0.0, 0);
	if(!Logo->is_initialized)
	{
		return false;
	}
	Button Play(Graphics, "Play", 150, 0);
	if(!Play.is_initialized)
	{
		return false;
	}
	Buttons.push_back(&Play);

	Button Quit(Graphics, "Quit", 150, 1);
	if(!Quit.is_initialized)
	{
		return false;
	}
	Buttons.push_back(&Quit);

	max_button_idx      = 1;
	selected_button_idx = 0;

	while(mode == primary_enabled)
	{
		// if(!Graphics.init_frame())
		// {
		// 	delete Logo;
		// 	return false;
		// }
		if(!Graphics.render_primary_menu(*this))
		{
			delete Logo;
			return false;
		}
		if(!Keyboard.menu(*this))
		{
			delete Logo;
			return false;
		}
		// Graphics.count_fps();
	}
	delete Logo;

	return true;
}

bool Menu::pause(Graphics& Graphics, Keyboard& Keyboard, Level& Level)
{
	Button Continue(Graphics, "Continue", 150, 0);
	if(!Continue.is_initialized)
	{
		return false;
	}
	Buttons.push_back(&Continue);

	Button Main_menu(Graphics, "Main menu", 150, 1);
	if(!Main_menu.is_initialized)
	{
		Buttons.clear();
		return false;
	}
	Buttons.push_back(&Main_menu);

	max_button_idx      = 1;
	selected_button_idx = 0;

	while(mode == pause_enabled)
	{
		if(!Graphics.render_pause_menu(*this, Level))
		{
			return false;
		}
		if(!Keyboard.pause(*this))
		{
			return false;
		}
	}

	return true;
}
