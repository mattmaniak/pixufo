#include "pixufo.hpp"

namespace sdl_wrapper
{
	void init()
	{
		const bool success = 0;

		if(SDL_Init(SDL_INIT_EVERYTHING) != success)
		{
			std::cerr << "Can't init the SDL." << std::endl;
			exit(1);
		}
	}

	SDL_Window* create_window()
	{
		char title[8] = "PixUfo";

		const unsigned int width  = 1280;
		const unsigned int height = 720;

		SDL_Window* new_window;

		new_window = SDL_CreateWindow
		(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			0
		);

		if(new_window == NULL)
		{
			std::cerr << "Can't create the window." << std::endl;
			exit(1);
		}
		return new_window;
	}

	SDL_Surface* load_bitmap(const char* path)
	{
		SDL_Surface* new_bitmap = SDL_LoadBMP(path);

		if(new_bitmap == NULL)
		{
			std::cerr << "Can't load the bitmap: " << path << '.' << std::endl;
			exit(1);
		}
		return new_bitmap;
	}
}

int main()
{
	sdl_wrapper::init();

	SDL_Event    event;
	SDL_Window*  window = sdl_wrapper::create_window();
	SDL_Surface* icon   = sdl_wrapper::load_bitmap("game/ingame_icon.bmp");

	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	// Close app after the user's event.
	for(; event.type != SDL_QUIT; SDL_PollEvent(&event));

	SDL_DestroyWindow(window);
	SDL_Quit();
}
