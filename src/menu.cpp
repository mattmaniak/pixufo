#include "graphics.hpp"
#include "menu.hpp"

bool Menu::main(SDL_Renderer* renderer)
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
	SDL_RenderClear(renderer);

	return true;
}

bool Menu::paused(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);

	return true;
}
