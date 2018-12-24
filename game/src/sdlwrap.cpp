#include "sdlwrap.hpp"

namespace sdlwrap
{
	SDL_Surface* load_image(SDL_Window* window, std::string path)
	{
		SDL_Surface* image = SDL_LoadBMP(path.c_str());

		if(image == NULL)
		{
			std::cerr << "Can't load the bitmap: " << path << '.' << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}
		return image;
	}
}
