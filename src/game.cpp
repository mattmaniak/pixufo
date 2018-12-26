#include "game.hpp"

Game::Game()
{
	const int       unused_size = 0;
	SDL_DisplayMode screen;

	if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
	{
		error("Can't initialize the SDL.");
	}

	if(SDL_GetDesktopDisplayMode(0, &screen) != SUCCESS)
	{
		error("Can't get the screen resolution.");
	}
	if((screen.w < GAME_RESOLUTION_W) || (screen.h < GAME_RESOLUTION_H))
	{
		error("At least HD screen resolution is required.");
	}

	window = SDL_CreateWindow(
	"PixUfo",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	GAME_RESOLUTION_W,
	GAME_RESOLUTION_H,
	SDL_WINDOW_FULLSCREEN);

	if(window == nullptr)
	{
		error("Can't create the window.");
	}
	SDL_SetWindowIcon(window, load_image("gfx/icon.bmp"));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr)
	{
		error("Can't create the renderer.");
	}
	// if(SDL_GetRendererOutputSize(renderer, &w, &h) != SUCCESS)
	// {
	// 	error("Can't get the renderer size.");
	// }
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SUCCESS)
	{
		std::cerr << "Can't hide the mouse." << std::endl;
	}
	background = load_texture("gfx/planet_orange.bmp");

	runtime = true;
}

SDL_Surface* Game::load_image(const std::string path)
{
	SDL_Surface* image = SDL_LoadBMP(path.c_str());
	if(image == nullptr)
	{
		error("Can't load the image: " + path);
	}
	return image;
}

SDL_Texture* Game::load_texture(const std::string path)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(
	renderer,
	load_image(path));

	if(texture == nullptr)
	{
		error("Can't create the texture: " + path);
	}
	return texture;
}

bool Game::quit()
{
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}
	if(window != nullptr)
	{
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return 0;
}

bool Game::error(const std::string message)
{
	std::cerr << message << std::endl;
	quit();
	return 1;
}

Game::~Game()
{
	std::cout << "Game destructor." << std::endl;
	quit();
}
