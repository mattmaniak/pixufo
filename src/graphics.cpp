#include "graphics.hpp"
#include "error.hpp"
#include "level.hpp"
#include "model.hpp"

Graphics::Graphics()
{
	const int unused_size    = 0;
	const int default_driver = -1;

	SDL_Surface* icon = load_image("icon");
	if(icon == nullptr)
	{
		error::show_box("Can't load the icon.");
		initialized = false;
		return;
	}
	if(SDL_GetDesktopDisplayMode(0, &Screen) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the desktop size.");
		initialized = false;
		return;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_size, unused_size,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(Window == nullptr)
	{
		error::show_box("Can't create the window.");
		initialized = false;
		return;
	}
	if((Screen.w < MIN_DISPLAY_WIDTH) || (Screen.h < MIN_DISPLAY_HEIGHT))
	{
		error::show_box("At least the HD display resolution is required.");
		initialized = false;
		return;
	}
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);

	Renderer = SDL_CreateRenderer(Window, default_driver,
	                              SDL_RENDERER_ACCELERATED
	                              | SDL_RENDERER_PRESENTVSYNC);
	if(Renderer == nullptr)
	{
		error::show_box("Can't create the renderer.");
		initialized = false;
		return;
	}
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS)
	{
		error::show_box("Can't hide the mouse pointer.");
		initialized = false;
		return;
	}
	fps = 0;
	frame_elapsed_time = 0.0f;

	initialized = true;
}

Graphics::~Graphics()
{
	if(Renderer != nullptr)
	{
		SDL_DestroyRenderer(Renderer);
	}
	if(Window != nullptr)
	{
		SDL_DestroyWindow(Window);
	}
}

SDL_Texture* Graphics::load_texture(const std::string name)
{
	const std::string directory = "textures";
	const std::string extension = "bmp";

#ifdef _WIN32
	const std::string path = directory + '\\' + name + '.' + extension;

#else
#ifdef __linux__
	const std::string path = directory + '/' + name + '.' + extension;
#endif

#endif

	SDL_Surface* Image = SDL_LoadBMP(path.c_str());
	SDL_Texture* Texture;

	if(Image == nullptr)
	{
		error::show_box("Can't load the image: " + path);
		return nullptr;
	}

	Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	if(Texture == nullptr)
	{
		error::show_box("Can't create the texture from image: " + path);
	}
	SDL_FreeSurface(Image);

	return Texture;
}

void Graphics::start_fps_count()
{
	frame_start_time = SDL_GetTicks() / 1000.0f;
}

bool Graphics::count_fps()
{
	fps++;

	if(fps >= std::numeric_limits<Uint32>::max())
	{
		error::show_box("Too many frames per second.");
		return false;
	}

	delta_time = ((SDL_GetTicks() / 1000.0f) - frame_start_time);
	frame_elapsed_time += delta_time;

	if(frame_elapsed_time >= 1.0f)
	{
		fps                = 0;
		frame_elapsed_time = 0.0f;
	}
	return true;
}

bool Graphics::tile_background(model::Background* Background)
{
	// + 1 - extra one for scrolling.
	unsigned int tiles_x = (Screen.w / Background->Geometry.w) + 1;
	unsigned int tiles_y = (Screen.h / Background->Geometry.h) + 1;

	if((tiles_x >= std::numeric_limits<unsigned int>::max())
	|| (tiles_y >= std::numeric_limits<unsigned int>::max()))
	{
		error::show_box("Too many tiles in the background.");
		return false;
	}

	// Scrolling.
	if(Background->pos_x > 0) // Background shifted right.
	{
		// Move the background one tile left.
		Background->pos_x -= Background->Geometry.w;
	}
	else if(Background->pos_x < -Background->Geometry.w) // Background shifted left.
	{
		// Move the background one tile right.
		Background->pos_x += Background->Geometry.w;
	}
	if(Background->pos_y > 0) // Background shifted down.
	{
		// Move the background one tile up.
		Background->pos_y -= Background->Geometry.h;
	}
	else if(Background->pos_y < -Background->Geometry.h) // Background shifted up.
	{
		// Move the background one tile down.
		Background->pos_y += Background->Geometry.h;
	}

	// Tiling.
	for(unsigned int y = 0; y <= tiles_y; y++)
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Background->Geometry.x = Background->pos_x
			                         + (x * Background->Geometry.w);

			Background->Geometry.y = Background->pos_y
			                         + (y * Background->Geometry.h);

			if(SDL_RenderCopy(Renderer, Background->Texture, nullptr,
			   &Background->Geometry) != SDL2_SUCCESS)
			{
				error::show_box("Can't render the background texture.");
				return false;
			}
		}
	}
	return true;
}

bool Graphics::render_level(Level* Level)
{
	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer.");
		return false;
	}

	// Level->Background->pos_x -= 0.25f;
	// Level->Background->pos_y -= 0.25f;

	tile_background(Level->Background);

	Level->Background->Geometry.x = Level->Background->pos_x;
	Level->Background->Geometry.y = Level->Background->pos_y;

	Level->Background->step = Level->Background->speed
	                          * Level->Background->count_scale()
	                          * delta_time;

	for(size_t idx = 0; idx < Level->Enemies.size(); idx++)
	{
		Level->Enemies[idx]->Geometry.x = Level->Enemies[idx]->pos_x;
		Level->Enemies[idx]->Geometry.y = Level->Enemies[idx]->pos_y;

		if(SDL_RenderCopy(Renderer, Level->Enemies[idx]->Texture, nullptr,
		   &Level->Enemies[idx]->Geometry) != SDL2_SUCCESS)
		{
			error::show_box("Can't render the enemy's texture.");
			return false;
		}

		Level->Enemies[idx]->step = Level->Enemies[idx]->speed
		                            * Level->Enemies[idx]->count_scale()
		                            * delta_time;
	}

	Level->Player->Geometry.x = Level->Player->pos_x;
	Level->Player->Geometry.y = Level->Player->pos_y;

	if(SDL_RenderCopy(Renderer, Level->Player->Texture, nullptr,
	   &Level->Player->Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't render the player's texture.");
		return false;
	}

	Level->Player->step = Level->Player->speed * Level->Player->count_scale()
	                      * delta_time;

	SDL_RenderPresent(Renderer);

	return true;
}

SDL_Surface* load_image(const std::string name)
{
	const std::string directory = "textures";
	const std::string extension = "bmp";

#ifdef _WIN32
	const std::string path = directory + '\\' + name + '.' + extension;

#else
#ifdef __linux__
	const std::string path = directory + '/' + name + '.' + extension;
#endif

#endif

	SDL_Surface* image = SDL_LoadBMP(path.c_str());

	if(image == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	return image;
}
