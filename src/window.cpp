#include "sdlwrap.hpp"
#include "window.hpp"

Window::Window()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
	{
		_error("Can't initialize the SDL.");
	}
	if(SDL_GetDesktopDisplayMode(0, &display) != SUCCESS)
	{
		_error("Can't get the initial display mode.");
	}
	if((display.w < MIN_RESOLUTION_W) || (display.h < MIN_RESOLUTION_H))
	{
		_error("At least the HD display resolution is required.");
	}

	window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, UNUSED_SIZE,
	                          UNUSED_SIZE, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(window == nullptr)
	{
		_error("Can't create the window.");
	}
	SDL_SetWindowIcon(window, sdlwrap::load_image("gfx/icon.bmp"));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
	                              | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr)
	{
		_error("Can't create the renderer.");
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SUCCESS)
	{
		_error("Can't hide the mouse.");
	}
}

SDL_Texture* Window::create_texture(SDL_Surface* image)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	if(texture == nullptr)
	{
		_error("Can't create a texture.");
	}
	return texture;
}

Window::~Window()
{

}

void Window::count_fps()
{
	if(++fps >= std::numeric_limits<Uint32>::max())
	{
		std::cerr << "Too many frames per second." << std::endl;
		// return 1;
		return;
	}
	delta_time = ((SDL_GetTicks() / 1000.0f) - frame_start_time);

	if((frame_elapsed_time += delta_time) >= 1.0f)
	{
		fps = 0;
		frame_elapsed_time = 0.0f;
	}
}

void Window::quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::_error(const std::string message)
{
	std::cerr << message << std::endl;
	quit();
	exit(1);
}
