#include "pixufo.hpp"

namespace sdl_wrapper
{
	void init()
	{
		const bool success = 0;

		if(SDL_Init(SDL_INIT_EVERYTHING) != success)
		{
			std::cerr << "Can't init the SDL." << std::endl;
			exit(1);
		}
	}

	SDL_Window* create_window()
	{
		std::string title = "PixUfo";

		const unsigned int width  = 1280;
		const unsigned int height = 720;

		SDL_Window* new_window;

		new_window = SDL_CreateWindow
		(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_SHOWN
		);

		if(new_window == NULL)
		{
			std::cerr << "Can't create the window." << std::endl;
			exit(1);
		}
		return new_window;
	}

	SDL_Surface* load_bitmap(std::string path)
	{
		SDL_Surface* new_bitmap = SDL_LoadBMP(path.c_str());

		if(new_bitmap == NULL)
		{
			std::cerr << "Can't load the bitmap: " << path << '.' << std::endl;
			exit(1);
		}
		return new_bitmap;
	}

	void set_icon(SDL_Window* window_to_set, std::string path)
	{
		SDL_Surface* icon = sdl_wrapper::load_bitmap(path.c_str());

		if(icon == NULL)
		{
			std::cerr << "Can't load the icon: " << path << std::endl;
		}
		SDL_SetWindowIcon(window_to_set, icon);
		SDL_FreeSurface(icon);
	}
}

int main()
{
	sdl_wrapper::init();

	SDL_Event     event;
	SDL_Window*   window   = sdl_wrapper::create_window();
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	sdl_wrapper::set_icon(window, "icon.bmp");

	// Converts the surface to the texture.
	SDL_Surface* logo         = sdl_wrapper::load_bitmap("gfx/superscription.bmp");
	SDL_Texture* texture      = SDL_CreateTextureFromSurface(renderer, logo);
	SDL_Rect     logo_pos_sz  = {300, 100, 860, 380};
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

	// Close app after the user's event.
	for(; event.type != SDL_QUIT; SDL_PollEvent(&event));

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
