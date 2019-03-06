#include "menu.hpp"
#include "level.hpp"

New_menu::New_menu(Graphics& Graphics):
Scene(Graphics, "background_primary_menu")
{

}

New_menu::~New_menu()
{

}

bool Main_menu::render()
{

	return true;
}

Menu::Menu(Graphics& Graphics):
Scene(Graphics, "background_primary_menu"), mode(primary_enabled)
{
	is_initialized = false;

	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	Select_arrow = new Sprite(Graphics, "planet_orange", 0);
	if(!Select_arrow->is_initialized)
	{
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
	Logo = new Sprite(Graphics, "title", 0);
	if(!Logo->is_initialized)
	{
		return false;
	}
	Button Play(Graphics, "Play", 40, 0);
	if(!Play.is_initialized)
	{
		return false;
	}
	Buttons.push_back(&Play);

	Button Quit(Graphics, "Quit", 40, 1);
	if(!Quit.is_initialized)
	{
		return false;
	}
	Buttons.push_back(&Quit);

	selected_button_idx = 0;

	// while(mode == primary_enabled)
	// {
		Graphics.set_up_new_frame();
		if(!Graphics.render_primary_menu(*this))
		{
			delete Logo;
			return false;
		}
	// }
	Buttons.clear();
	delete Logo;

	return true;
}

bool Menu::pause(Graphics& Graphics, Keyboard& Keyboard, Level& Level)
{
	Button Continue(Graphics, "Continue", 40, 0);
	if(!Continue.is_initialized)
	{
		return false;
	}
	Buttons.push_back(&Continue);

	Button Main_menu(Graphics, "Main menu", 40, 1);
	if(!Main_menu.is_initialized)
	{
		Buttons.clear();
		return false;
	}
	Buttons.push_back(&Main_menu);

	selected_button_idx = 0;

	if(!Graphics.render_pause_menu(*this, Level))
	{
		return false;
	}
	Buttons.clear();

	return true;
}
