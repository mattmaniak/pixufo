#include "graphics.hpp"
#include "menu.hpp"
#include "level.hpp"

Graphics::Graphics()
{
	const int unused_sz      = 0;
	const int default_driver = -1;

	SDL_Surface* icon;

	if(SDL_GetDisplayBounds(CURRENT_DISPLAY_IDX, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the screen size at the initialization.");
		is_initialized = false;
		return;
	}

	if((Display.w < MIN_DISPLAY_WIDTH) || (Display.h < MIN_DISPLAY_HEIGHT))
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
	if(SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't set the renderer blend mode.");
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
	const std::string path      = directory + SEPARATOR + name + FILE_EXTENSION;

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
	SDL_GetWindowSize(Window, &Display.w, &Display.h);

	pixelart_px_sz = Display.w / PIXELART_DISPLAY_WIDTH;

	return true;
}

bool Graphics::init_frame(Level& Level)
{
	frame_start_time_ms = SDL_GetTicks();

	Prev_display = Display;

	if(!get_pixelart_px_sz())
	{
		return false;
	}
	if((Display.w != Prev_display.w) || (Display.h != Prev_display.h))
	{
		Level.set_entities_borders(*this);
	}
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

#ifdef DEBUG
		std::cout << "FPS: " << fps << std::endl;
#endif

		frame_elapsed_time_ms = 0.0;
		fps                   = 0;
	}
	return true;
}

bool Graphics::render_level(Level& Level, const bool as_pause_menu_bg)
{
	if(!clean_renderer())
	{
		return false;
	}
	if(!Level.Bg->tile_and_render(*this))
	{
		return false;
	}

	for(std::size_t idx = 0; idx < Level.enemies_amount; idx++)
	{
		if(!Level.Enemies[idx]->render(*this))
		{
			return false;
		}
		Level.Enemies[idx]->move(*this, -Level.Enemies[idx]->max_speed, 0.0);
	}
	if(!Level.Ufo->render(*this))
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
	if(!Menu.Bg->tile_and_render(*this))
	{
		return false;
	}
	// Menu.Bg->move(*this, -5.0, 2.5);

	Menu.Logo->pos_x = Menu.Logo->pos_y = padding;

	if(!Menu.Logo->render(*this))
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
		Menu.Buttons[idx]->pos_x = (Display.w - Menu.Buttons[idx]->Geometry.w)
		                           - padding;

		Menu.Buttons[idx]->pos_y = Display.h - (Menu.Buttons[idx]->Geometry.h
		                           * (Menu.max_button_idx + 1))
		                           + (Menu.Buttons[idx]->idx
		                           * Menu.Buttons[idx]->Geometry.h) - padding;

		Menu.Buttons[idx]->Geometry.x = Menu.Buttons[idx]->pos_x;
		Menu.Buttons[idx]->Geometry.y = Menu.Buttons[idx]->pos_y;

		if(!render_font(*Menu.Buttons[idx]))
		{
			return false;
		}
		if(Menu.Buttons[idx]->idx == Menu.selected_button_idx)
		{
			Menu.Select_arrow->pos_x = Menu.Buttons[idx]->Geometry.x
			                           - Menu.Select_arrow->Geometry.w;

			Menu.Select_arrow->pos_y = Menu.Buttons[idx]->Geometry.y;
		}
		Menu.Buttons[idx]->Geometry.x = Menu.Buttons[idx]->pos_x;
		Menu.Buttons[idx]->Geometry.y = Menu.Buttons[idx]->pos_y;

		if(!Menu.Select_arrow->render(*this))
		{
			return false;
		}
	}
	return true;
}
