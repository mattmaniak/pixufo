#include "menu.hpp"
#include "level.hpp"

Menu::Menu(Graphics& Graphics): Scene(Graphics, "background_primary_menu"),
                                selected_button_idx(0)
{
	Sprites.insert(std::make_pair("title", new Sprite(Graphics, "title", 0)));
	Sprites.insert(std::make_pair("selection_arrow", new Sprite(Graphics,
	                                                            "meteor", 0)));
	has_text                = false;
	selection_arrow_focused = true;
}

Menu::~Menu()
{
	delete Sprites["title"];
	delete Sprites["selection_arrow"];

	Sprites.clear();
}

bool Menu::render(Graphics& Graphics)
{
	if(!Bg->tile_and_render(Graphics))
	{
		return false;
	}

	Sprites["title"]->pos_x = Sprites["title"]->pos_y = PADDING;
	if(!Sprites["title"]->render(Graphics))
	{
		return false;
	}

	for(std::size_t idx = 0; idx < Buttons.size(); idx++)
	{
		Buttons[idx]->pos_x = PADDING;
		Buttons[idx]->pos_y = Graphics.Display.h - (Buttons[idx]->Geometry.h
		                      * Buttons.size()) + (idx
		                      * Buttons[idx]->Geometry.h) - PADDING;

		Buttons[idx]->Geometry.x = Buttons[idx]->pos_x;
		Buttons[idx]->Geometry.y = Buttons[idx]->pos_y;

		if(!Buttons[idx]->render(Graphics))
		{
			return false;
		}
		if(idx == selected_button_idx)
		{
			Sprites["selection_arrow"]->pos_x = Buttons[idx]->Geometry.w
			                                    + PADDING;

			Sprites["selection_arrow"]->pos_y = Buttons[idx]->Geometry.y;
		}
		Buttons[idx]->Geometry.x = Buttons[idx]->pos_x;
		Buttons[idx]->Geometry.y = Buttons[idx]->pos_y;

	}
	if(selection_arrow_focused)
	{
		if(!Sprites["selection_arrow"]->render(Graphics))
		{
			return false;
		}
	}
	if(has_text)
	{
		for(auto& Line: Text_lines)
		{
			if(!Line->render(Graphics))
			{
				return false;
			}
		}
	}
	SDL_RenderPresent(Graphics.Renderer);

	return true;
}

Main_menu::Main_menu(Graphics& Graphics): Menu(Graphics)
{
	try
	{
		Buttons.push_back(new Font(Graphics, "Play", MAIN_FONT_SZ));
		Buttons.push_back(new Font(Graphics, "Credits", MAIN_FONT_SZ));
		Buttons.push_back(new Font(Graphics, "Quit", MAIN_FONT_SZ));
	}
	catch(...)
	{
		throw std::runtime_error("");
	}
}

Main_menu::~Main_menu()
{
	for(auto& Button: Buttons)
	{
		delete Button;
	}
}

bool Main_menu::keyboard_steering(states& state)
{
	SDL_Event Event;
	SDL_PollEvent(&Event);

	switch(Event.type)
	{
	case SDL_QUIT:
		return false;

	case SDL_KEYDOWN:
		switch(Event.key.keysym.sym)
		{
		case SDLK_UP:
			if(selected_button_idx > 0)
			{
				selected_button_idx--;
			}
			break;

		case SDLK_DOWN:
			if(selected_button_idx < (Buttons.size() - 1))
			{
				selected_button_idx++;
			}
			break;

		case SDLK_RETURN:
			switch(selected_button_idx)
			{
			case 0:
				state = level;
				break;

			case 1:
				state = credits_menu;
				break;

			case 2:
				return false;
			}
		}
	}
	return true;
}

Pause_menu::Pause_menu(Graphics& Graphics): Menu(Graphics)
{
	try
	{
		Buttons.push_back(new Font(Graphics, "Continue", MAIN_FONT_SZ));
		Buttons.push_back(new Font(Graphics, "Break", MAIN_FONT_SZ));
	}
	catch(...)
	{
		throw std::runtime_error("");
	}
}

Pause_menu::~Pause_menu()
{
	for(auto& Button: Buttons)
	{
		delete Button;
	}
}

bool Pause_menu::keyboard_steering(states& state)
{
	SDL_Event Event;
	SDL_PollEvent(&Event);

	switch(Event.type)
	{
	case SDL_QUIT:
		return false;
	}
	switch(Event.key.keysym.sym)
	{
	case SDLK_UP:
		if(selected_button_idx > 0)
		{
			selected_button_idx--;
		}
		break;

	case SDLK_DOWN:
		if(selected_button_idx < (Buttons.size() - 1))
		{
			selected_button_idx++;
		}
		break;

		case SDLK_RETURN:
		switch(selected_button_idx)
		{
		case 0:
			state = level;
			break;

		case 1:
			state = main_menu;
		}
	}
	return true;
}

Credits_menu::Credits_menu(Graphics& Graphics): Menu(Graphics)
{
	const double text_leading = 1.5;

	try
	{
		Buttons.push_back(new Font(Graphics, "Return", MAIN_FONT_SZ));

		Text_lines.push_back(new Font(Graphics, "Programming", TEXT_FONT_SZ));
		Text_lines.push_back(new Font(Graphics, "mattmaniak", TEXT_FONT_SZ));
		Text_lines.push_back(new Font(Graphics, "Graphics", TEXT_FONT_SZ));
		Text_lines.push_back(new Font(Graphics, "Jakub QooBooS Mieszczak",
		                              TEXT_FONT_SZ));

		// Center the lines.
		for(std::size_t idx = 0; idx < Text_lines.size(); idx++)
		{
			Text_lines[idx]->pos_x = Graphics.Display.w - PADDING
			                         - Text_lines[idx]->Geometry.w;

			Text_lines[idx]->pos_y = PADDING;
			if(idx > 0)
			{
				Text_lines[idx]->pos_y = Text_lines[idx - 1]->pos_y
				                         + (Text_lines[idx - 1]->sz * text_leading);
			}
		}
		has_text = true;
	}
	catch(...)
	{
		throw std::runtime_error("");
	}
	selected_button_idx     = 1;
	selection_arrow_focused = false;
}

Credits_menu::~Credits_menu()
{
	for(auto& Button: Buttons)
	{
		delete Button;
	}
	for(auto& Line: Text_lines)
	{
		delete Line;
	}
	Buttons.clear();
	Text_lines.clear();
}


bool Credits_menu::keyboard_steering(states& state)
{
	SDL_Event Event;
	SDL_PollEvent(&Event);

	switch(Event.type)
	{
	case SDL_QUIT:
		return false;
	}
	switch(Event.key.keysym.sym)
	{
	case SDLK_UP:
	case SDLK_DOWN:
		selected_button_idx     = 0;
		selection_arrow_focused = true;
		break;

	case SDLK_RETURN:
		switch(selected_button_idx)
		{
		case 0:
			state = main_menu;
		}
	}
	return true;
}
