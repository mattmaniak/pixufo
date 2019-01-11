#include "sdlwrap.hpp"
#include "window.hpp"

Window::Window()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
	{
		_error();
	}
	if(SDL_GetDesktopDisplayMode(0, &Display) != SUCCESS)
	{
		_error();
	}
	if((Display.w < MIN_RESOLUTION_W) || (Display.h < MIN_RESOLUTION_H))
	{
		std::cerr << "At least the HD display resolution is required." << std::endl;
		SDL_ClearError();
		_error();
	}
	window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, UNUSED_SIZE,
	                          UNUSED_SIZE, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(window == nullptr)
	{
		_error();
	}
	SDL_SetWindowIcon(window, sdlwrap::load_image("icon"));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
	                              | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		_error();
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SUCCESS)
	{
		_error();
	}
}

SDL_Texture* Window::create_texture(SDL_Surface* Image)
{
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, Image);

	if(Texture == nullptr)
	{
		_error();
	}
	return Texture;
}

Window::~Window()
{

}

int Window::count_fps()
{
	if(++fps >= std::numeric_limits<Uint32>::max())
	{
		std::cerr << "Too many frames per second." << std::endl;
		return -1;
	}
	delta_time = ((SDL_GetTicks() / 1000.0f) - frame_start_time);

	if((frame_elapsed_time += delta_time) >= 1.0f)
	{
		fps = 0;
		frame_elapsed_time = 0.0f;
	}
	return 0;
}

void Window::destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::_error()
{
	std::cerr << SDL_GetError() << std::endl;
	destroy();
	exit(1);
}
