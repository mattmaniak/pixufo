#include "pixufo.hpp"

class Game
{
	void _set_icon();
	bool _quit();

	public:
	bool          runtime;
	int           w;
	int           h;
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
		error("Can't initialize the SDL.");
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
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SUCCESS)
	{
		error("Can't hide the mouse.");
	}
	if(SDL_GetRendererOutputSize(renderer, &w, &h) != SUCCESS)
	{
		error("Can't get the renderer size.");
	}
}

void Game::_set_icon()
{
	SDL_Surface* icon = sdlwrap::load_image(window, "game/textures/icon.bmp");

	if(icon == NULL)
	{
		error("Can't load the icon.");
	}
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
}

bool Game::error(std::string message)
{
	std::cerr << message << std::endl;
	_quit();
	return 1;
}

bool Game::_quit()
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
	_quit();
}

class Model
{
	public:
	SDL_Surface* image;     // Just a bitmap and some metadata.
	SDL_Texture* texture;   // Driver-specific representation of data.
	SDL_Rect     rectangle; // Texture's position and size.
	int          move;      // Pixels offset that can move in a single frame.

	Model(int _x, int _y, int _move) : move(_move)
	{
		rectangle.x = _x;
		rectangle.y = _y;
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
	Model Ufo(0, 0, 8);

	// Converts the surface to the texture.
	Ufo.image = sdlwrap::load_image(PixUfo.window, "game/textures/ufo.bmp");
	Ufo.texture = SDL_CreateTextureFromSurface(PixUfo.renderer, Ufo.image);

	if(Ufo.texture == NULL)
	{
		PixUfo.error("Can't crete the texture.");
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
				if(Ufo.rectangle.y >= Ufo.move)
				{
					Ufo.rectangle.y -= Ufo.move;
				}
				break;

				case SDLK_DOWN:
				if((Ufo.rectangle.y + Ufo.rectangle.h + Ufo.move) <= PixUfo.h)
				{
					Ufo.rectangle.y += Ufo.move;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.rectangle.x >= Ufo.move)
				{
					Ufo.rectangle.x -= Ufo.move;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.rectangle.x + Ufo.rectangle.w + Ufo.move) <= PixUfo.w)
				{
					Ufo.rectangle.x += Ufo.move;
				}
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
