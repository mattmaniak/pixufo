#include "pixufo.hpp"

class Game
{
	public:
		int           window_w;
		int           window_h;
		SDL_Event     event;
		SDL_Window*   window;
		SDL_Renderer* renderer;
		SDL_Surface*  model;

		Game();
		void set_icon();
		void stop();
		~Game();
};

Game::Game()
{
	window_w = 1280;
	window_h = 720;

	if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
	{
		std::cerr << "Can't initialize the SDL." << std::endl;
		return;
	}

	// Creates the window.
	window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_FULLSCREEN);

	if(window == NULL)
	{
		std::cerr << "Can't create the window." << std::endl;
		stop();
	}

//	sdlwrap::set_icon(window, "game/textures/icon.bmp");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::set_icon()
{
	SDL_Surface* icon = sdlwrap::load_bitmap(window, "game/textures/icon.bmp");

	if(icon == NULL)
	{
		std::cerr << "Can't load the icon." << std::endl;
		stop();
	}
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
}

void Game::stop()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(model);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}

Game::~Game()
{
	stop();
}

int main()
{
	Game PixUfo;

	// Converts the surface to the texture.
	PixUfo.model = sdlwrap::load_bitmap(PixUfo.window, "game/textures/title.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(PixUfo.renderer, PixUfo.model);

	if(texture == NULL)
	{
		std::cerr << "Can't crete the texture." << std::endl;
		exit(1);
		// TODO: DESTROY AND QUIT.
	}
	SDL_Rect title_pos_sz = {0, 0, RESIZE_SURFACE(PixUfo.model)};
//	SDL_FreeSurface(PixUfo.model); CAUSES SEGV!

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
}
