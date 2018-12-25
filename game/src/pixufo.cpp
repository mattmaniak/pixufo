#include "pixufo.hpp"

class Game
{
	void set_icon();
	bool stop();

	public:
	bool          runtime;
	int           width;
	int           height;
	SDL_Event     event;
	SDL_Window*   window;
	SDL_Renderer* renderer;

	Game();
	bool error(std::string message);
	~Game();
};

Game::Game()
{
	runtime = true;

	if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS)
	{
		std::cerr << "Can't initialize the SDL." << std::endl;
		stop();
	}

	/* According to the SDL_CreateWindow wiki: "If the window is set fullscreen,
	the width and height parameters w and h will not be used." 0, 0 -> w, h. */
	window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

	if(window == NULL)
	{
		error("Can't create the window.");
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		error("Can't create the renderer.");
	}
	if(SDL_GetRendererOutputSize(renderer, &width, &height) != SUCCESS)
	{
		error("Can't get the renderer size.");
	}
}

void Game::set_icon()
{
	SDL_Surface* icon = sdlwrap::load_image(window, "game/textures/icon.bmp");

	if(icon == NULL)
	{
		std::cerr << "Can't load the icon." << std::endl;
		stop();
	}
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
}

bool Game::error(std::string message)
{
	std::cerr << message << std::endl;
	stop();
	return 1;
}

bool Game::stop()
{
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return 0;
}

Game::~Game()
{
	stop();
}

class Model
{
	public:
	SDL_Surface* image;     // Just a bitmap and some metadata.
	SDL_Texture* texture;   // Driver-specific representation of data.
	SDL_Rect     rectangle; // Texture's position and size.
	// int          x;
	// int          y;

	Model(int x, int y)
	//: rectangle.x(x), rectangle.y(y)
	{
		rectangle.x = x;
		rectangle.y = y;
		// rectangle.w = image->w * SCALE_FACTOR;
		// rectangle.h = image->h * SCALE_FACTOR;
		// image = sdlwrap::load_image()
	}
	~Model()
	{
		SDL_FreeSurface(image);
		SDL_DestroyTexture(texture);
	}
};

int main()
{
	Game  PixUfo;
	Model Ufo(0, 0);

	// Converts the surface to the texture.
	Ufo.image = sdlwrap::load_image(PixUfo.window, "game/textures/ufo.bmp");
	Ufo.texture = SDL_CreateTextureFromSurface(PixUfo.renderer, Ufo.image);

	if(Ufo.texture == NULL)
	{
		std::cerr << "Can't crete the texture." << std::endl;
		exit(1);
		// TODO: DESTROY AND QUIT.
	}
	Ufo.rectangle.w = Ufo.image->w * SCALE_FACTOR;
	Ufo.rectangle.h = Ufo.image->h * SCALE_FACTOR;

	while(PixUfo.runtime) // Close the game after the user's event.
	{
		SDL_PollEvent(&PixUfo.event);
		switch(PixUfo.event.type)
		{
			default:
			break;

			case SDL_QUIT:
			PixUfo.runtime = false;
			break;

			case SDL_KEYDOWN: // TODO: AND KEYUP?
			switch(PixUfo.event.key.keysym.sym)
			{
				default:
				break;

				case SDLK_UP:
				Ufo.rectangle.y -= 8;
				break;

				case SDLK_DOWN:
				Ufo.rectangle.y += 8;
				break;

				case SDLK_LEFT:
				Ufo.rectangle.x -= 8;
				break;

				case SDLK_RIGHT:
				Ufo.rectangle.x += 8;
				break;
			}
			break;
		}
		// Copies and displays the beautiful title.
		SDL_SetRenderDrawColor(PixUfo.renderer, 20, 0, 10, 255);
		SDL_RenderClear(PixUfo.renderer);
		SDL_RenderCopy(PixUfo.renderer, Ufo.texture, NULL, &Ufo.rectangle);
		SDL_RenderPresent(PixUfo.renderer);

		SDL_UpdateWindowSurface(PixUfo.window);

//		SDL_Delay(FRAME_DELAY);
	}
}
