#include "sdl_wrapper.hpp"

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
		std::string title = "PixUfo";

		const unsigned int width = 1280;
		const unsigned int height = 720;

		SDL_Window* new_window;

		new_window = SDL_CreateWindow
		(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_FULLSCREEN
		);

		if(new_window == NULL)
		{
			std::cerr << "Can't create the window." << std::endl;
			exit(1);
		}
		return new_window;
	}

	SDL_Surface* load_bitmap(std::string path)
	{
		SDL_Surface* new_bitmap = SDL_LoadBMP(path.c_str());

		if(new_bitmap == NULL)
		{
			std::cerr << "Can't load the bitmap: " << path << '.' << std::endl;
			exit(1);
		}
		return new_bitmap;
	}

	void set_icon(SDL_Window* window_to_set, std::string path)
	{
		SDL_Surface* icon = sdl_wrapper::load_bitmap(path.c_str());

		if(icon == NULL)
		{
			std::cerr << "Can't load the icon: " << path << std::endl;
		}
		SDL_SetWindowIcon(window_to_set, icon);
		SDL_FreeSurface(icon);
	}
}
