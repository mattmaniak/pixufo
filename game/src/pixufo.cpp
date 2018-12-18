#include "pixufo.hpp"

int main()
{
	sdl_wrapper::init();

	SDL_Event event;
	SDL_Window* window = sdl_wrapper::create_window();

	SDL_Renderer* renderer =
	SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	sdl_wrapper::set_icon(window, "gfx/icon.bmp");

	// Converts the surface to the texture.
	SDL_Surface* logo = sdl_wrapper::load_bitmap("gfx/title.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, logo);
	SDL_Rect logo_pos_sz = {300, 100, 860, 380};

	SDL_FreeSurface(logo);

	if(texture == NULL)
	{
		std::cerr << "Can't crete the texture." << std::endl;
		exit(1);
	}

	// Copies and displays the beautiful ufo.
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, &logo_pos_sz);
	SDL_RenderPresent(renderer);

	while(true) // Close the game after the user's event.
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			break;
		}
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
