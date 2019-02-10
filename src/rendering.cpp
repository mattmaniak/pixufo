#include "rendering.hpp"
#include "error.hpp"
#include "level.hpp"
#include "background.hpp"
#include "player.hpp"
#include "menu.hpp"
#include "button.hpp"
#include "enemy.hpp"

Rendering::Rendering()
{
	const int unused_sz      = 0;
	const int default_driver = -1;

	SDL_Surface* icon = load_image("icon");
	if(icon == nullptr)
	{
		error::show_box("Can't load the icon.");
		initialized = false;
		return;
	}
	if(SDL_GetDesktopDisplayMode(CURRENT_DISPLAY, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the desktop size.");
		initialized = false;
		return;
	}
	Window = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, unused_sz, unused_sz,
	                          SDL_WINDOW_FULLSCREEN_DESKTOP);
	if(Window == nullptr)
	{
		error::show_box("Can't create the window.");
		initialized = false;
		return;
	}
	if((Display.w < MIN_DISPLAY_WIDTH) || (Display.h < MIN_DISPLAY_HEIGHT))
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

Rendering::~Rendering()
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

SDL_Surface* Rendering::load_image(const std::string name)
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
		error::show_box("Can't load the image: " + name);
	}
	return image;
}

SDL_Texture* Rendering::load_texture(const std::string name)
{
	SDL_Surface* Image = load_image(name);
	SDL_Texture* Texture;

	if(Image == nullptr)
	{
		error::show_box("Can't load the image: " + name);
		return nullptr;
	}

	Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	if(Texture == nullptr)
	{
		error::show_box("Can't create the texture from image: " + name);
	}
	SDL_FreeSurface(Image);

	return Texture;
}

float Rendering::pixelart_pixel_sz()
{
	if(SDL_GetCurrentDisplayMode(CURRENT_DISPLAY, &Display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the current display size.");
		initialized = false;
	}
	return Display.w / PIXELART_DISPLAY_WIDTH;
}

void Rendering::start_fps_count()
{
	frame_start_time = SDL_GetTicks();
}

bool Rendering::count_fps()
{
	fps++;

	if(fps >= std::numeric_limits<Uint32>::max())
	{
		error::show_box("Too many frames per second.");
		return false;
	}

	delta_time = (SDL_GetTicks() - frame_start_time) / 1000.0f;
	frame_elapsed_time += delta_time * 1000;

	if(frame_elapsed_time >= 1000)
	{
		fps                = 0;
		frame_elapsed_time = 0.0f;
	}
	return true;
}

bool Rendering::tile_background(Background* Space)
{
	// + 1 - extra one for scrolling.
	unsigned int tiles_x = (Display.w / Space->Geometry.w) + 1;
	unsigned int tiles_y = (Display.h / Space->Geometry.h) + 1;

	if((tiles_x >= std::numeric_limits<unsigned int>::max())
	|| (tiles_y >= std::numeric_limits<unsigned int>::max()))
	{
		error::show_box("Too many tiles in the background.");
		return false;
	}

	// Scrolling.
	if(Space->pos_x > Space->max_x) // Space shifted right.
	{
		// Move the background one tile left.
		Space->pos_x -= Space->Geometry.w;
	}
	else if(Space->pos_x < Space->min_x) // Space shifted left.
	{
		// Move the background one tile right.
		Space->pos_x += Space->Geometry.w;
	}
	if(Space->pos_y > Space->max_y) // Space shifted down.
	{
		// Move the background one tile up.
		Space->pos_y -= Space->Geometry.h;
	}
	else if(Space->pos_y < Space->min_y) // Space shifted up.
	{
		// Move the background one tile down.
		Space->pos_y += Space->Geometry.h;
	}

	// Tiling.
	for(unsigned int y = 0; y <= tiles_y; y++)
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Space->Geometry.x = Space->pos_x + (x * Space->Geometry.w);
			Space->Geometry.y = Space->pos_y + (y * Space->Geometry.h);

			if(SDL_RenderCopy(Renderer, Space->Texture, nullptr,
			   &Space->Geometry) != SDL2_SUCCESS)
			{
				error::show_box("Can't render the background texture.");
				return false;
			}
		}
	}
	return true;
}

bool Rendering::render_level(Level* Level)
{
	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer.");
		return false;
	}

	// Level->Space->pos_x -= 0.25f;
	// Level->Space->pos_y -= 0.25f;

	tile_background(Level->Space);

	Level->Space->Geometry.x = Level->Space->pos_x;
	Level->Space->Geometry.y = Level->Space->pos_y;

	Level->Space->step = Level->Space->max_speed * delta_time * pixelart_pixel_sz();

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

		Level->Enemies[idx]->step = Level->Enemies[idx]->max_speed * delta_time
		                            * pixelart_pixel_sz();
	}

	Level->Ufo->Geometry.x = Level->Ufo->pos_x;
	Level->Ufo->Geometry.y = Level->Ufo->pos_y;

	if(SDL_RenderCopy(Renderer, Level->Ufo->Texture, nullptr,
	   &Level->Ufo->Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't render the player's texture.");
		return false;
	}

	Level->Ufo->step = Level->Ufo->max_speed * delta_time * pixelart_pixel_sz();

	SDL_RenderPresent(Renderer);

	return true;
}

bool Rendering::render_primary_menu(Menu* Menu)
{
	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer in the primary menu.");
		return false;
	}

	for(unsigned int idx = 0; idx <= Menu->max_button_idx; idx++)
	{
		Menu->Buttons[idx]->Geometry.x = (Display.w
		                                 - Menu->Buttons[idx]->Geometry.w) / 2;

		Menu->Buttons[idx]->Geometry.y = (Display.h / 2)
		                                 + (Menu->Buttons[idx]->idx
		                                 * Menu->Buttons[idx]->Geometry.h);

		// Selected button shift.
		if(Menu->Buttons[idx]->idx == Menu->selected_button_idx)
		{
			Menu->Buttons[idx]->Geometry.x += SELECTED_BUTTON_SHIFT
			                                  * pixelart_pixel_sz();
		}

		if(SDL_RenderCopy(Renderer, Menu->Buttons[idx]->Texture, nullptr,
		   &Menu->Buttons[idx]->Geometry) != SDL2_SUCCESS)
		{
			error::show_box("Can't copy a texture: " + Menu->Buttons[idx]->name
			                + " to the renderer.");
			return false;
		}
	}
	SDL_RenderPresent(Renderer);

	return true;
}

bool Rendering::render_pause_menu(Menu* Menu)
{
	if(SDL_RenderClear(Renderer) != SDL2_SUCCESS)
	{
		error::show_box("Can't clean the renderer in the pause menu.");
		return false;
	}

	for(unsigned int idx = 0; idx <= Menu->max_button_idx; idx++)
	{
		Menu->Buttons[idx]->Geometry.x = (Display.w
		                                 - Menu->Buttons[idx]->Geometry.w) / 2;

		Menu->Buttons[idx]->Geometry.y = (Display.h / 2)
		                                 + (Menu->Buttons[idx]->idx
		                                 * Menu->Buttons[idx]->Geometry.h);

		// Selected button shift.
		if(Menu->Buttons[idx]->idx == Menu->selected_button_idx)
		{
			Menu->Buttons[idx]->Geometry.x += SELECTED_BUTTON_SHIFT
			                                  * pixelart_pixel_sz();
		}

		if(SDL_RenderCopy(Renderer, Menu->Buttons[idx]->Texture, nullptr,
		   &Menu->Buttons[idx]->Geometry) != SDL2_SUCCESS)
		{
			error::show_box("Can't copy a texture: " + Menu->Buttons[idx]->name
			                + " to the renderer.");
			return false;
		}
	}
	SDL_RenderPresent(Renderer);

	return true;
}
