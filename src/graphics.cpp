#include "graphics.hpp"
#include "error.hpp"
#include "level.hpp"
#include "background.hpp"
#include "player.hpp"
#include "menu.hpp"
#include "button.hpp"
#include "entity.hpp"

Graphics::Graphics()
{
	const int unused_sz      = 0;
	const int default_driver = -1;

	SDL_Surface* icon = load_image("icon");
	if(icon == nullptr)
	{
		error::show_box("Can't load the icon.");
		initialized = false;
		return;
	}
	if(SDL_GetDesktopDisplayMode(CURRENT_DISPLAY, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the desktop size.");
		initialized = false;
		return;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_sz, unused_sz,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(Window == nullptr)
	{
		error::show_box("Can't create the window.");
		initialized = false;
		return;
	}
	if((Display.w < MIN_DISPLAY_WIDTH) || (Display.h < MIN_DISPLAY_HEIGHT))
	{
		error::show_box("At least the HD display resolution is required.");
		initialized = false;
		return;
	}
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);

	Renderer = SDL_CreateRenderer(Window, default_driver,
	                              SDL_RENDERER_ACCELERATED
	                              | SDL_RENDERER_PRESENTVSYNC);
	if(Renderer == nullptr)
	{
		error::show_box("Can't create the renderer.");
		initialized = false;
		return;
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS)
	{
		error::show_box("Can't hide the mouse pointer.");
		initialized = false;
		return;
	}
	delta_time_s          = 0.0f;
	frame_elapsed_time_ms = 0.0f;
	fps                   = 0;

	initialized = true;
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

float Graphics::pixelart_px_sz()
{
	if(SDL_GetCurrentDisplayMode(CURRENT_DISPLAY, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the current display size.");
		initialized = false;
	}
	return Display.w / PIXELART_DISPLAY_WIDTH;
}

void Graphics::start_fps_count()
{
	frame_start_time_ms = SDL_GetTicks();
}

bool Graphics::count_fps()
{
	fps++;

	if(fps >= std::numeric_limits<Uint32>::max())
	{
		error::show_box("Too many frames per second.");
		return false;
	}
	delta_time_s = (SDL_GetTicks() - frame_start_time_ms) / 1000.0f;
	frame_elapsed_time_ms += delta_time_s * 1000.0f;

	if(frame_elapsed_time_ms >= 1000.0f)
	{
		frame_elapsed_time_ms = 0.0f;
		fps                   = 0;
	}
	return true;
}

bool Graphics::render_tiled_background(Background* Bg)
{
	// + 1 - extra one for scrolling.
	unsigned int tiles_x = (Display.w / Bg->Geometry.w) + 1;
	unsigned int tiles_y = (Display.h / Bg->Geometry.h) + 1;

	if((tiles_x >= std::numeric_limits<unsigned int>::max())
	   || (tiles_y >= std::numeric_limits<unsigned int>::max()))
	{
		error::show_box("Too many tiles in the background.");
		return false;
	}
	Bg->inf_scroll();

	for(unsigned int y = 0; y <= tiles_y; y++) // Tiling.
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Bg->Geometry.x = Bg->pos_x + (x * Bg->Geometry.w);
			Bg->Geometry.y = Bg->pos_y + (y * Bg->Geometry.h);

			if(!render_model(Bg))
			{
				return false;
			}
		}
	}
	return true;
}

bool Graphics::render_level(Level* Level, const bool pause_menu_bg)
{
	if(!clean_renderer())
	{
		return false;
	}
	Level->Space_bg->calc_pos(this);
	render_tiled_background(Level->Space_bg);

	for(std::size_t idx = 0; idx < Level->enemies_amount; idx++)
	{
		Level->Enemies[idx]->calc_pos(this);

		if(!render_model(Level->Enemies[idx]))
		{
			return false;
		}
	}
	Level->Ufo->calc_pos(this);

	if(!render_model(Level->Ufo))
	{
		return false;
	}

	if(pause_menu_bg)
	{
		delta_time_s = 0.0f; // Disable animations
	}
	else
	{
		SDL_RenderPresent(Renderer);
	}
	return true;
}

bool Graphics::render_primary_menu(Menu* Menu)
{
	const float padding = 20.0f * pixelart_px_sz();

	if(!clean_renderer())
	{
		return false;
	}
	Menu->Space_bg->move(this, -5.0f, 2.5f);
	Menu->Space_bg->calc_pos(this);

	if(!render_tiled_background(Menu->Space_bg))
	{
		return false;
	}

	Menu->Logo->pos_x = Menu->Logo->pos_y = padding;
	Menu->Logo->calc_pos(this);

	if(!render_model(Menu->Logo))
	{
		return false;
	}
	render_buttons(Menu);
	SDL_RenderPresent(Renderer);

	return true;
}

bool Graphics::render_pause_menu(Menu* Menu, Level* Level)
{
	render_level(Level, true);
	render_buttons(Menu);

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

bool Graphics::render_model(Model* Model)
{
	Model->animate(this);

	if(SDL_RenderCopy(Renderer, Model->Textures[Model->current_frame_idx],
	   nullptr, &Model->Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't copy the texture: " + Model->name
		                + " to the renderer.");
		return false;
	}
	return true;
}

bool Graphics::render_buttons(Menu* Menu)
{
	const float padding = 20.0f * pixelart_px_sz();

	for(std::size_t idx = 0; idx <= Menu->max_button_idx; idx++)
	{
		Menu->Buttons[idx]->Geometry.x = (Display.w
		                                 - Menu->Buttons[idx]->Geometry.w)
		                                 - padding;

		Menu->Buttons[idx]->Geometry.y = Display.h
		                                 - (Menu->Buttons[idx]->Geometry.h
		                                 * (Menu->max_button_idx + 1))
		                                 + (Menu->Buttons[idx]->idx
		                                 * Menu->Buttons[idx]->Geometry.h)
		                                 - padding;

		if(!render_model(Menu->Buttons[idx]))
		{
			return false;
		}

		if(Menu->Buttons[idx]->idx == Menu->selected_button_idx)
		{
			Menu->Select_arrow->Geometry.x = Menu->Buttons[idx]->Geometry.x
			                                 - Menu->Select_arrow->Geometry.w;

			Menu->Select_arrow->Geometry.y = Menu->Buttons[idx]->Geometry.y;
		}
		if(!render_model(Menu->Select_arrow))
		{
			return false;
		}
	}
	return true;
}
