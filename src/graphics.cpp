#include "graphics.hpp"
#include "menu.hpp"
#include "level.hpp"

Graphics::Graphics()
{
	const int unused_sz      = 0;
	const int default_driver = -1;

	SDL_Surface* icon;

	// if(SDL_GetDesktopDisplayMode(CURRENT_SCREEN_IDX, &Display_mode)
	//    != SDL2_SUCCESS)
	// {
	// 	error::show_box("Can't get the screen size at the initialization.");
	// 	is_initialized = false;
	// 	return;
	// }
	if(SDL_GetDisplayBounds(CURRENT_SCREEN_IDX, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the screen size at the initialization.");
		is_initialized = false;
		return;
	}

	if((Display.w < MIN_DISPLAY_WIDTH)
	   || (Display.h < MIN_DISPLAY_HEIGHT))
	{
		error::show_box("At least the HD screen resolution is required.");
		is_initialized = false;
		return;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_sz, unused_sz,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);

	if(Window == nullptr)
	{
		error::show_box("Can't create the window.");
		is_initialized = false;
		return;
	}

	icon = load_image("icon");
	if(icon == nullptr)
	{
		error::show_box("Can't load the window icon.");
		is_initialized = false;
		return;
	}
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);

	Renderer = SDL_CreateRenderer(Window, default_driver,
	                              SDL_RENDERER_ACCELERATED);
	if(Renderer == nullptr)
	{
		error::show_box("Can't create the renderer.");
		is_initialized = false;
		return;
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS)
	{
		error::show_box("Can't hide the mouse pointer.");
		is_initialized = false;
		return;
	}
	delta_time_s          = 0.0;
	frame_elapsed_time_ms = 0.0;
	fps                   = 0;

	if(!get_pixelart_px_sz())
	{
		is_initialized = false;
		return;
	}
	// Prev_display_mode = Display_mode;
	Prev_display = Display;

	is_initialized = true;
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
}

SDL_Surface* Graphics::load_image(const std::string name)
{
	const std::string directory = "textures";

#ifdef _WIN32
	const std::string separator = "\\";

#else
#ifdef __linux__
	const std::string separator = "/";
#endif

#endif

	const std::string path = directory + separator + name + FILE_EXTENSION;

	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		error::show_box("Can't load the image: " + path);
	}
	return image;
}

SDL_Texture* Graphics::load_texture(const std::string name)
{
	SDL_Texture* Texture;
	SDL_Surface* Image = load_image(name);

	if(Image == nullptr)
	{
		return nullptr;
	}

	Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	if(Texture == nullptr)
	{
		error::show_box("Can't create the texture from the image: " + name);
	}
	SDL_FreeSurface(Image);

	return Texture;
}

bool Graphics::get_pixelart_px_sz()
{
	if(SDL_GetDisplayBounds(CURRENT_SCREEN_IDX, &Display)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get the screen size at the initialization.");
		return false;
	}
	// if(SDL_GetDesktopDisplayMode(CURRENT_SCREEN_IDX, &Display_mode)
	//    != SDL2_SUCCESS)
	// {
	// 	error::show_box("Can't get the current display size.");
	// 	return false;
	// }
	// if((Display_mode.w < MIN_DISPLAY_WIDTH)
	//    || (Display_mode.h < MIN_DISPLAY_HEIGHT))
	// {
	// 	error::show_box("Current screen resolution is smaller than HD.");
	// 	return false;
	// }
	pixelart_px_sz = Display.w / PIXELART_DISPLAY_WIDTH;

	return true;
}

bool Graphics::init_frame(Level& Level)
{
	frame_start_time_ms = SDL_GetTicks();

	// Prev_display_mode = Display_mode;

	if(!get_pixelart_px_sz())
	{
		return false;
	}
	if(SDL_GetDisplayUsableBounds(CURRENT_SCREEN_IDX, &Display)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get the screen size at the initialization.");
		return false;
	}
	if((Display.w != Prev_display.w) // Game resolution has changed.
	   || (Display.h != Prev_display.h))
	{
		std::cout << "DODO" << std::endl;

		if(SDL_GetDisplayBounds(CURRENT_SCREEN_IDX, &Display)
		   != SDL2_SUCCESS)
		{
			error::show_box("Can't get the screen size at the initialization.");
			return false;
		}
		Level.set_entities_borders(*this);

		if(SDL_GetDisplayUsableBounds(CURRENT_SCREEN_IDX, &Display)
		   != SDL2_SUCCESS)
		{
			error::show_box("Can't get the screen size at the initialization.");
			return false;
		}
	}
	Prev_display = Display;

	std::cout << "DM: " << Display.w << ' ' << Display.h
	<< " PV: " << Prev_display.w << ' ' << Prev_display.h << std::endl;

	return true;
}

bool Graphics::count_fps()
{
	fps++;

	if(fps >= std::numeric_limits<Uint32>::max())
	{
		error::show_box("Too many frames per second.");
		return false;
	}
	delta_time_s = (SDL_GetTicks() - frame_start_time_ms) / 1000.0;
	frame_elapsed_time_ms += delta_time_s * 1000.0;

	if(frame_elapsed_time_ms >= 1000.0)
	{

#ifdef DEBUG_ON_LINUX
		std::cout << "FPS: " << fps << std::endl;
#endif

		frame_elapsed_time_ms = 0.0;
		fps                   = 0;
	}
	return true;
}

bool Graphics::render_tiled_background(Background& Bg)
{
	// + 1 - extra one for scrolling.
	unsigned int tiles_x = (Display.w / Bg.Geometry.w) + 1;
	unsigned int tiles_y = (Display.h / Bg.Geometry.h) + 1;

	if((tiles_x >= std::numeric_limits<unsigned int>::max())
	   || (tiles_y >= std::numeric_limits<unsigned int>::max()))
	{
		error::show_box("Too many tiles in the background.");
		return false;
	}
	Bg.inf_scroll();

	for(unsigned int y = 0; y <= tiles_y; y++) // Tiling.
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Bg.Geometry.x = Bg.pos_x + (x * Bg.Geometry.w);
			Bg.Geometry.y = Bg.pos_y + (y * Bg.Geometry.h);

			if(!render_model(Bg))
			{
				return false;
			}
		}
	}
	return true;
}

bool Graphics::render_level(Level& Level, const bool as_pause_menu_bg)
{
	if(!clean_renderer())
	{
		return false;
	}
	Level.Space_bg->calc_pos(*this);
	render_tiled_background(*Level.Space_bg);

	for(std::size_t idx = 0; idx < Level.enemies_amount; idx++)
	{
		Level.Enemies[idx]->calc_pos(*this);

		if(!render_model(*Level.Enemies[idx]))
		{
			return false;
		}
		Level.Enemies[idx]->move(*this, -Level.Enemies[idx]->max_speed, 0.0);
	}
	Level.Ufo->calc_pos(*this);

	if(!render_model(*Level.Ufo))
	{
		return false;
	}

	if(as_pause_menu_bg)
	{
		delta_time_s = 0.0; // Disable animations
	}
	else
	{
		SDL_RenderPresent(Renderer);
	}
	return true;
}

bool Graphics::render_primary_menu(Menu& Menu)
{
	const double padding = 20.0 * pixelart_px_sz;

	if(!clean_renderer())
	{
		return false;
	}
	Menu.Space_bg->calc_pos(*this);

	if(!render_tiled_background(*Menu.Space_bg))
	{
		return false;
	}
	Menu.Space_bg->move(*this, -5.0, 2.5f);

	Menu.Logo->pos_x = Menu.Logo->pos_y = padding;
	Menu.Logo->calc_pos(*this);

	if(!render_model(*Menu.Logo))
	{
		return false;
	}
	if(!render_buttons(Menu))
	{
		return false;
	}
	SDL_RenderPresent(Renderer);

	return true;
}

bool Graphics::render_pause_menu(Menu& Menu, Level& Level)
{
	render_level(Level, true);

	if(!render_buttons(Menu))
	{
		return false;
	}
	SDL_RenderPresent(Renderer);

	return true;
}

bool Graphics::clean_renderer()
{
	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer.");
		return false;
	}
	return true;
}

bool Graphics::render_model(Model& Model)
{
	Model.animate(*this);

	if(SDL_RenderCopy(Renderer, Model.Textures[Model.current_frame_idx],
	   nullptr, &Model.Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't copy the texture: " + Model.name
		                + " to the renderer.");
		return false;
	}
	return true;
}

bool Graphics::render_font(Font& Font)
{
	if(SDL_RenderCopy(Renderer, Font.Texture, nullptr, &Font.Geometry)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't copy the texture: " + Font.name
		                + " to the renderer.");
		return false;
	}
	return true;
}

bool Graphics::render_buttons(Menu& Menu)
{
	const double padding = 20.0 * pixelart_px_sz;

	for(std::size_t idx = 0; idx <= Menu.max_button_idx; idx++)
	{
		Menu.Buttons[idx]->Geometry.x = (1920
		                                - Menu.Buttons[idx]->Geometry.w)
		                                - padding;

		Menu.Buttons[idx]->Geometry.y = 1080
		                                - (Menu.Buttons[idx]->Geometry.h
		                                * (Menu.max_button_idx + 1))
		                                + (Menu.Buttons[idx]->idx
		                                * Menu.Buttons[idx]->Geometry.h)
		                                - padding;

		if(!render_font(*Menu.Buttons[idx]))
		{
			return false;
		}

		if(Menu.Buttons[idx]->idx == Menu.selected_button_idx)
		{
			Menu.Select_arrow->Geometry.x = Menu.Buttons[idx]->Geometry.x
			                                - Menu.Select_arrow->Geometry.w;

			Menu.Select_arrow->Geometry.y = Menu.Buttons[idx]->Geometry.y;
		}
		if(!render_model(*Menu.Select_arrow))
		{
			return false;
		}
	}
	return true;
}
