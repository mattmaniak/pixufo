#include "pixufo.hpp"

void init_sdl()
{
	const bool success = 0;

	if(SDL_Init(SDL_INIT_VIDEO) != success)
	{
		std::cerr << "Can't init the SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

SDL_Window* create_window()
{
	const char* title = "PixUfo\0";

	const unsigned int width = 1280;
	const unsigned int height = 720;

	SDL_Window* new_window;

	new_window = SDL_CreateWindow
	(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);

	if(new_window == NULL)
	{
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		exit(1);
	}
	return new_window;
}

int main()
{
	init_sdl();

	SDL_Window* window = create_window();

	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
}
