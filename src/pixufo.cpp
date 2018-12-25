#include "pixufo.hpp"

class Game
{
	public:
	bool          runtime;
	int           w;
	int           h;
	SDL_Event     event;
	SDL_Window*   window;
	SDL_Renderer* renderer;

	Game();
	bool quit();
	bool error(std::string message);
	~Game();
};

Game::Game()
{
	SDL_Surface* icon;

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
		std::cerr << "Can't hide the mouse." << std::endl;
	}

	if(SDL_GetRendererOutputSize(renderer, &w, &h) != SUCCESS)
	{
		error("Can't get the renderer size.");
	}

	icon = SDL_LoadBMP("gfx/icon.bmp");
	if(icon == NULL)
	{
		std::cerr << "Can't load the icon." << std::endl;
	}
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	runtime = true;
}

bool Game::error(std::string message)
{
	std::cerr << message << std::endl;
	quit();
	return 1;
}

bool Game::quit()
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
	quit();
}

class Character
{
	bool error(std::string message);

	public:
	SDL_Surface* image;   // Just a bitmap and some metadata.
	SDL_Texture* texture; // Driver-specific representation of data.
	SDL_Rect     model;   // Texture's position and size.
	int          step;    // Pixels offset that can step in a single frame.

	Character(const Game* game, std::string image_path, int _x, int _y, int _step);
	bool destroy();
	~Character();
};

bool Character::error(std::string message)
{
	std::cerr << message << std::endl;
	destroy();
	return 1;
}

Character::Character(const Game* game, std::string image_path, int _x, int _y,
int _step) : step(_step)
{
	model.x = _x;
	model.y = _y;

	image = SDL_LoadBMP(image_path.c_str());
	if(image == NULL)
	{
		error("Can't load the image: " + image_path);
	}

	texture = SDL_CreateTextureFromSurface(game->renderer, image);
	if(texture == NULL)
	{
		error("Can't create the texture from: " + image_path);
	}
	model.w = image->w * SCALE_FACTOR;
	model.h = image->h * SCALE_FACTOR;
}

bool Character::destroy()
{
	if(image != NULL)
	{
		SDL_FreeSurface(image);
	}
	if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
	}
	return 0;
}

Character::~Character()
{
	destroy();
}

int main()
{
	Game      PixUfo;
	Character Ufo(&PixUfo, "gfx/ufo.bmp", 0, 0, 8);

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
				if(Ufo.model.y >= Ufo.step)
				{
					Ufo.model.y -= Ufo.step;
				}
				break;

				case SDLK_DOWN:
				if((Ufo.model.y + Ufo.model.h + Ufo.step) <= PixUfo.h)
				{
					Ufo.model.y += Ufo.step;
				}
				break;

				case SDLK_LEFT:
				if(Ufo.model.x >= Ufo.step)
				{
					Ufo.model.x -= Ufo.step;
				}
				break;

				case SDLK_RIGHT:
				if((Ufo.model.x + Ufo.model.w + Ufo.step) <= PixUfo.w)
				{
					Ufo.model.x += Ufo.step;
				}
				break;
			}
			break;
		}
		// Copies and displays the beautiful title.
		SDL_SetRenderDrawColor(PixUfo.renderer, 20, 0, 10, 255);
		SDL_RenderClear(PixUfo.renderer);
		SDL_RenderCopy(PixUfo.renderer, Ufo.texture, NULL, &Ufo.model);
		SDL_RenderPresent(PixUfo.renderer);

		SDL_UpdateWindowSurface(PixUfo.window);

//		SDL_Delay(FRAME_DELAY);
	}
}
