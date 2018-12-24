#include "sdlwrap.hpp"

namespace sdlwrap
{
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
		SDL_Surface* icon = sdlwrap::load_bitmap(window, path.c_str());

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
