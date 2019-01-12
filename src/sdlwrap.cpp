#include "sdlwrap.hpp"

SDL_Surface* sdlwrap::load_image(const std::string name)
{
	std::string directory = "gfx";
	std::string extension = "bmp";

#ifdef __linux__
	std::string path = directory+ '/' + name + '.' + extension;
#endif

#ifdef _WIN32
	std::string path = directory + '\\' + name + '.' + extension;
#endif

	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	return image;
}
