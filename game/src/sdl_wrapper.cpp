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

		SDL_Window* window;

		window = SDL_CreateWindow
		(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_FULLSCREEN
		);

		if(window == NULL)
		{
			std::cerr << "Can't create the window." << std::endl;
			SDL_Quit();
			exit(1);
		}
		return window;
	}

	SDL_Surface* load_bitmap(SDL_Window* window, std::string path)
	{
		SDL_Surface* bitmap = SDL_LoadBMP(path.c_str());

		if(bitmap == NULL)
		{
			std::cerr << "Can't load the bitmap: " << path << '.' << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}
		return bitmap;
	}

	void set_icon(SDL_Window* window, std::string path)
	{
		SDL_Surface* icon = sdl_wrapper::load_bitmap(window, path.c_str());

		if(icon == NULL)
		{
			std::cerr << "Can't load the icon: " << path << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}
}
