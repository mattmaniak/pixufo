#include "sdlwrap.hpp"

SDL_Surface* sdlwrap::load_image(const std::string path)
{
	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		std::cerr << "Can't load the image: " << path << std::endl;
		exit(1); // TODO.
	}
	return image;
}
