#include "game.hpp"

Game::Game()
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
	SDL_SetWindowIcon(window, load_image("gfx/icon.bmp"));

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

Game::~Game()
{
	quit();
}

SDL_Surface* Game::load_image(const std::string path)
{
	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		_error("Can't load the image: " + path);
	}
	return image;
}

SDL_Texture* Game::create_texture(SDL_Surface* image)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	if(texture == nullptr)
	{
		_error("Can't create a texture.");
	}
	return texture;
}

void Game::loop()
{
	// TODO
}

void Game::keyboard()
{

}

void Game::quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::_error(const std::string message)
{
	std::cerr << message << std::endl;
	quit();
	exit(1);
}
