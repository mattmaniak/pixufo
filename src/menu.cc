#include "menu.h"
#include "level.h"

Menu::Menu(Graphics& graphics): Scene(graphics, "background_primary_menu"), selected_button_idx(0)
{
	try
	{
	Sprites.insert(std::make_pair("title", new Sprite(graphics, "title", 0)));
	Sprites.insert(std::make_pair("selection_arrow", new Sprite(graphics, "meteor", 0)));
	}
	catch (std::runtime_error)
	{
		throw std::runtime_error("");
	}
	has_text                = false;
	selection_arrow_focused = true;
}

Menu::~Menu()
{
	delete Sprites["title"];
	delete Sprites["selection_arrow"];

	Sprites.clear();
}

bool Menu::render(Graphics& graphics)
{
	if (!Bg->tile_and_render(graphics))
	{
		return false;
	}

	Sprites["title"]->pos_x = Sprites["title"]->pos_y = PADDING;
	if (!Sprites["title"]->render(graphics))
	{
		return false;
	}

	for (std::size_t idx = 0; idx < buttons.size(); idx++)
	{
		buttons[idx]->pos_x = PADDING;
		buttons[idx]->pos_y = graphics.Display.h - (buttons[idx]->geometry.h * buttons.size()) + (idx * buttons[idx]->geometry.h) - PADDING;

		buttons[idx]->geometry.x = buttons[idx]->pos_x;
		buttons[idx]->geometry.y = buttons[idx]->pos_y;

		if (!buttons[idx]->render(graphics))
		{
			return false;
		}
		if (idx == selected_button_idx)
		{
			Sprites["selection_arrow"]->pos_x = buttons[idx]->geometry.w + PADDING;
			Sprites["selection_arrow"]->pos_y = buttons[idx]->geometry.y;
		}
		buttons[idx]->geometry.x = buttons[idx]->pos_x;
		buttons[idx]->geometry.y = buttons[idx]->pos_y;

	}
	if (selection_arrow_focused)
	{
		if (!Sprites["selection_arrow"]->render(graphics))
		{
			return false;
		}
	}
	if (has_text)
	{
		for (auto& Line: Text_lines)
		{
			if (!Line->render(graphics))
			{
				return false;
			}
		}
	}
	SDL_RenderPresent(graphics.renderer);

	return true;
}

Main_menu::Main_menu(Graphics& graphics): Menu(graphics)
{
	try
	{
		buttons.push_back(new Font(graphics, "Play", MAIN_FONT_SZ));
		buttons.push_back(new Font(graphics, "Credits", MAIN_FONT_SZ));
		buttons.push_back(new Font(graphics, "Quit", MAIN_FONT_SZ));
	}
	catch (std::runtime_error)
	{
		throw std::runtime_error("");
	}
}

Main_menu::~Main_menu()
{
	for (auto& Button: buttons)
	{
		delete Button;
	}
}

bool Main_menu::keyboard_steering(State& state)
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
			if (selected_button_idx > 0)
			{
				selected_button_idx--;
			}
			break;

		case SDLK_DOWN:
			if (selected_button_idx < (buttons.size() - 1))
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

Pause_menu::Pause_menu(Graphics& graphics): Menu(graphics)
{
	try
	{
		buttons.push_back(new Font(graphics, "Continue", MAIN_FONT_SZ));
		buttons.push_back(new Font(graphics, "Break", MAIN_FONT_SZ));
	}
	catch (std::runtime_error)
	{
		throw std::runtime_error("");
	}
}

Pause_menu::~Pause_menu()
{
	for (auto& Button: buttons)
	{
		delete Button;
	}
}

bool Pause_menu::keyboard_steering(State& state)
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
		if (selected_button_idx > 0)
		{
			selected_button_idx--;
		}
		break;

	case SDLK_DOWN:
		if (selected_button_idx < (buttons.size() - 1))
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

Credits_menu::Credits_menu(Graphics& graphics): Menu(graphics)
{
	const double text_leading = 1.5;

	try
	{
		buttons.push_back(new Font(graphics, "Return", MAIN_FONT_SZ));

		Text_lines.push_back(new Font(graphics, "Programming", TEXT_FONT_SZ));
		Text_lines.push_back(new Font(graphics, "mattmaniak", TEXT_FONT_SZ));
		Text_lines.push_back(new Font(graphics, "graphics", TEXT_FONT_SZ));
		Text_lines.push_back(new Font(graphics, "Jakub QooBooS Mieszczak", TEXT_FONT_SZ));

		// Center the lines.
		for (std::size_t idx = 0; idx < Text_lines.size(); idx++)
		{
			Text_lines[idx]->pos_x = graphics.Display.w - PADDING - Text_lines[idx]->geometry.w;
			Text_lines[idx]->pos_y = PADDING;

			if (idx > 0)
			{
				Text_lines[idx]->pos_y = Text_lines[idx - 1]->pos_y + (Text_lines[idx - 1]->size * text_leading);
			}
		}
		has_text = true;
	}
	catch (std::runtime_error)
	{
		throw std::runtime_error("");
	}
	selected_button_idx     = 1;
	selection_arrow_focused = false;
}

Credits_menu::~Credits_menu()
{
	for (auto& Button: buttons)
	{
		delete Button;
	}
	for (auto& Line: Text_lines)
	{
		delete Line;
	}
	buttons.clear();
	Text_lines.clear();
}


bool Credits_menu::keyboard_steering(State& state)
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
