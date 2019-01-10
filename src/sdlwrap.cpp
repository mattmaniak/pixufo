#include "include/sdlwrap.hpp"

SDL_Surface* sdlwrap::load_image(const std::string path)
{
#ifdef _WIN32
	std::string paaath = "gfx\\" + path;
#else
	std::string paaath = "gfx/" + path;
#endif

	std::cout << "WORKS!" << std::endl;
	std::cout << paaath << std::endl;

	SDL_Surface* image = SDL_LoadBMP(paaath.c_str());

	if(image == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(1); // TODO.
	}
	return image;
}
