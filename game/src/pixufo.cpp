#include "pixufo.hpp"

class Game
{
	public:
	SDL_Event     event;
	SDL_Window*   window;
	SDL_Renderer* renderer;
	SDL_Texture** texture;
	SDL_Surface** surface;

	void init()
	{
		sdl_wrapper::init();

		window = sdl_wrapper::create_window();
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		sdl_wrapper::set_icon(window, "gfx/icon.bmp");
	}

	void end()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};

int main()
{
	Game PixUfo;
	PixUfo.init();

	// Converts the surface to the texture.
	SDL_Surface* title = sdl_wrapper::load_bitmap(PixUfo.window, "gfx/title.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(PixUfo.renderer, title);

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
		SDL_PollEvent(&PixUfo.event);
		if(PixUfo.event.type == SDL_QUIT)
		{
			break;
		}
		// Copies and displays the beautiful title.
		SDL_RenderClear(PixUfo.renderer);
		SDL_RenderCopy(PixUfo.renderer, texture, NULL, &title_pos_sz);
		SDL_RenderPresent(PixUfo.renderer);

		SDL_UpdateWindowSurface(PixUfo.window);
	}

	PixUfo.end();
}
