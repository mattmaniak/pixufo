#include "graphics.hpp"
#include "menu.hpp"

bool Menu::main(SDL_Renderer* Renderer)
{
	// Button Play;
	// Button Quit;

	// SDL_Surface* button_play = load_image("play");
	// SDL_Surface* button_quit = load_image("quit");
	//
	// if(button_play == nullptr)
	// {
	// 	return false;
	// }
	// if(button_quit == nullptr)
	// {
	// 	return false;
	// }
	if(SDL_RenderClear(Renderer) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Menu::paused(SDL_Renderer* Renderer)
{
	if(SDL_RenderClear(Renderer) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}
