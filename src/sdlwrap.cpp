#include "sdlwrap.hpp"

SDL_Surface* sdlwrap::load_image(const std::string name)
{
	std::string extension = "bmp";

#ifdef _WIN32
	std::string path = "gfx\\" + name + '.' + extension;
#endif

#ifdef __linux__
	std::string path = "gfx/" + name + '.' + extension;
#endif

	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(1); // TODO.
	}
	return image;
}
