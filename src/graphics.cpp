#include "sdlwrap.hpp"
#include "graphics.hpp"

Graphics::Graphics()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
	{
		_error();
	}
	if(SDL_GetDesktopDisplayMode(0, &Screen) != SUCCESS)
	{
		_error();
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, UNUSED_SIZE, UNUSED_SIZE,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(Window == nullptr)
	{
		_error();
	}
	if((Screen.w < MIN_RESOLUTION_W) || (Screen.h < MIN_RESOLUTION_H))
	{
		std::cerr << "At least the HD display resolution is required." << std::endl;
		SDL_ClearError();
		_error();
	}
	SDL_SetWindowIcon(Window, sdlwrap::load_image("icon"));

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED
	                              | SDL_RENDERER_PRESENTVSYNC);
	if(Renderer == nullptr)
	{
		_error();
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SUCCESS)
	{
		_error();
	}
	fps = 0;
	frame_elapsed_time = 0.0f;
}

SDL_Texture* Graphics::create_texture(SDL_Surface* Image)
{
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Image);

	if(Texture == nullptr)
	{
		_error();
	}
	return Texture;
}

Graphics::~Graphics()
{

}

int Graphics::render()
{
	return 0;
}

void Graphics::count_frame_start_time()
{
	frame_start_time = SDL_GetTicks() / 1000.0f;
}

int Graphics::count_elapsed_time()
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

void Graphics::destroy()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void Graphics::_error()
{
	std::cerr << SDL_GetError() << std::endl;
	destroy();
	exit(1);
}
