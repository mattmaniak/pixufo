#include "menu.hpp"
#include "level.hpp"

Menus::Menus(Graphics& Graphics):
Scene(Graphics, "background_primary_menu"), mode(primary_enabled)
{
	try
	{
		Select_arrow = new Sprite(Graphics, "planet_orange", 0);
	}
	catch(...)
	{
		throw std::runtime_error("");
	}
	width  = Graphics.Display.w;
	height = Graphics.Display.h;
}

Menus::~Menus()
{
	delete Select_arrow;
}

bool Menus::primary(Graphics& Graphics, Keyboard& Keyboard)
{
	Logo = new Sprite(Graphics, "title", 0);

	Button Play(Graphics, "Play", 40, 0);
	Buttons.push_back(&Play);

	Button Quit(Graphics, "Quit", 40, 1);
	Buttons.push_back(&Quit);

	selected_button_idx = 0;

	while(mode == primary_enabled)
	{
		Graphics.set_up_new_frame();

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
		if(!Graphics.count_fps())
		{
			delete Logo;
			return false;
		}
	}
	Buttons.clear();
	delete Logo;

	Graphics.set_up_new_frame();

	return true;
}

bool Menus::pause(Graphics& Graphics, Keyboard& Keyboard, Level& Level)
{
	Button Continue(Graphics, "Continue", 40, 0);
	Buttons.push_back(&Continue);

	Button Main_menu(Graphics, "Main menu", 40, 1);
	Buttons.push_back(&Main_menu);

	selected_button_idx = 0;

	while(mode == pause_enabled)
	{
		Graphics.set_up_new_frame();

		if(!Graphics.render_pause_menu(*this, Level))
		{
			return false;
		}
		if(!Keyboard.pause(*this))
		{
			return false;
		}
		if(!Graphics.count_fps())
		{
			return false;
		}
	}
	Buttons.clear();
	Graphics.set_up_new_frame();

	return true;
}
