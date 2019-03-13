#include "graphics.hpp"
#include "menu.hpp"
#include "level.hpp"

Graphics::Graphics(): delta_time_s(0.0), Renderer(nullptr),
                      renderer_initialized(false),
                      window_initialized(false), Window(nullptr),
                      frame_elapsed_time_ms(0.0), fps(0)
{
	const int default_driver = -1;

	if(!init_window())
	{
		throw std::runtime_error("");
	}

	Renderer = SDL_CreateRenderer(Window, default_driver,
	                              SDL_RENDERER_ACCELERATED);
	if(Renderer == nullptr)
	{
		error::show_box("Can't create the renderer.");
		throw std::runtime_error("");
	}
	renderer_initialized = true;

	if(SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't enable the renderer blend mode.");
		throw std::runtime_error("");
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS)
	{
		error::show_box("Can't hide the mouse pointer.");
		throw std::runtime_error("");
	}
	get_pixelart_px_sz();
}

Graphics::~Graphics()
{
	if(renderer_initialized)
	{
		SDL_DestroyRenderer(Renderer);
		renderer_initialized = false;
	}
	if(window_initialized)
	{
		SDL_DestroyWindow(Window);
		window_initialized = false;
	}
}

bool Graphics::init_window()
{
	const int         unused_sz = 0;
	SDL_Surface*      Icon      = nullptr;
	const std::string icon_path = TEXTURES_PATH + "icon" + IMAGE_EXTENSION;

	if(SDL_GetDisplayBounds(CURRENT_DISPLAY_IDX, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the screen size at the initialization.");
		return false;
	}
	if((Display.w < MIN_DISPLAY_WIDTH) || (Display.h < MIN_DISPLAY_HEIGHT))
	{
		error::show_box("At least the HD screen resolution is required.");
		return false;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_sz, unused_sz,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);

	if(Window == nullptr)
	{
		error::show_box("Can't create the window.");
		return false;
	}
	window_initialized = true;

	Icon = SDL_LoadBMP(icon_path.c_str());
	if(Icon == nullptr)
	{
		return false;
	}
	SDL_SetWindowIcon(Window, Icon);
	SDL_FreeSurface(Icon);

	return true;
}

void Graphics::get_pixelart_px_sz()
{
	SDL_GetWindowSize(Window, &Display.w, &Display.h);

	pixelart_px_sz = Display.w / PIXELART_DISPLAY_WIDTH;

}

bool Graphics::set_up_new_frame()
{
	frame_start_time_ms = SDL_GetTicks();

	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer.");
		return false;
	}
	Prev_display = Display;
	get_pixelart_px_sz();

	if(((Display.w != Prev_display.w) || (Display.h != Prev_display.h))
	   && ((Display.w != 1) && (Display.h != 1))) // Minimized window.
	{
		return true; // Changed resolution.
	}
	return false;
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
		std::cout << "FPS: " << fps << std::endl;

		frame_elapsed_time_ms = 0.0;
		fps                   = 0;
	}
	return true;
}

bool Graphics::render_primary_menu(Menus& Menus)
{
	const double padding = 20.0 * pixelart_px_sz;

	if(!Menus.Bg->tile_and_render(*this))
	{
		return false;
	}
	Menus.Bg->move(*this, -5.0, 2.5);

	Menus.Logo->pos_x = Menus.Logo->pos_y = padding;

	if(!Menus.Logo->render(*this))
	{
		return false;
	}
	if(!render_buttons(Menus))
	{
		return false;
	}
	SDL_RenderPresent(Renderer);

	return true;
}

bool Graphics::render_pause_menu(Menus& Menus, Level& Level)
{
	if(!Menus.Bg->tile_and_render(*this))
	{
		return false;
	}
	Menus.Bg->move(*this, -5.0, 2.5);

	if(!render_buttons(Menus))
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

bool Graphics::render_buttons(Menus& Menus)
{
	const double padding = 20.0 * pixelart_px_sz;

	for(std::size_t idx = 0; idx < Menus.Buttons.size(); idx++)
	{
		Menus.Buttons[idx]->pos_x = (Display.w - Menus.Buttons[idx]->Geometry.w)
		                           - padding;

		Menus.Buttons[idx]->pos_y = Display.h - (Menus.Buttons[idx]->Geometry.h
		                           * Menus.Buttons.size())
		                           + (Menus.Buttons[idx]->idx
		                           * Menus.Buttons[idx]->Geometry.h) - padding;

		Menus.Buttons[idx]->Geometry.x = Menus.Buttons[idx]->pos_x;
		Menus.Buttons[idx]->Geometry.y = Menus.Buttons[idx]->pos_y;

		if(!render_font(*Menus.Buttons[idx]))
		{
			return false;
		}
		if(idx == Menus.selected_button_idx)
		{
			Menus.Select_arrow->pos_x = Menus.Buttons[idx]->Geometry.x
			                           - Menus.Select_arrow->Geometry.w;

			Menus.Select_arrow->pos_y = Menus.Buttons[idx]->Geometry.y;
		}
		Menus.Buttons[idx]->Geometry.x = Menus.Buttons[idx]->pos_x;
		Menus.Buttons[idx]->Geometry.y = Menus.Buttons[idx]->pos_y;

		if(!Menus.Select_arrow->render(*this))
		{
			return false;
		}
	}
	return true;
}
