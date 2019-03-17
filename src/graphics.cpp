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
		throw error::Exception_box("Can't create the renderer.");
	}
	renderer_initialized = true;

	if(SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND)
	   != SDL2_SUCCESS)
	{
		throw error::Exception_box("Can't enable the renderer blend mode.");
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS)
	{
		throw error::Exception_box("Can't hide the mouse pointer.");
	}
	if(!get_pixelart_px_sz())
	{
		throw std::runtime_error("");
	}
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
	const std::string icon_name = "icon.bmp";

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

	Icon = SDL_LoadBMP(icon_name.c_str());
	if(Icon == nullptr)
	{
		return false;
	}
	SDL_SetWindowIcon(Window, Icon);
	SDL_FreeSurface(Icon);

	return true;
}

bool Graphics::get_pixelart_px_sz()
{
	SDL_GetWindowSize(Window, &Display.w, &Display.h);

	if((Display.w > MAX_DISPLAY_WIDTH) || (Display.h > MAX_DISPLAY_HEIGHT))
	{
		error::show_box("Given display size is too big.");
		return false;
	}
	pixelart_px_sz = Display.w / PIXELART_DISPLAY_WIDTH;

	return true;
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

	if(!get_pixelart_px_sz())
	{
		return false;
	}

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

bool Graphics::clean_renderer()
{
	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer.");
		return false;
	}
	return true;
}
