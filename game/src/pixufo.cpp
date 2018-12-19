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
	SDL_Surface* title = sdl_wrapper::load_bitmap(window, "gfx/title.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, title);

	if(texture == NULL)
	{
		std::cerr << "Can't crete the texture." << std::endl;
		exit(1);
		// TODO: DESTROY AND QUIT.
	}
	SDL_FreeSurface(title);
	SDL_Rect title_pos_sz = {0, 0, STRETCH_BITMAP(title)};

	while(true) // Close the game after the user's event.
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			break;
		}
		// Copies and displays the beautiful title.
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &title_pos_sz);
		SDL_RenderPresent(renderer);

		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
