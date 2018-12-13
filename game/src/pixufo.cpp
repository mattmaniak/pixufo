#include "pixufo.hpp"

int main()
{
	SDL_Window* window;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Can't init the SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow
	(
		"PixUfo",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		SDL_WINDOW_OPENGL
	);
	if(window == NULL)
	{
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
