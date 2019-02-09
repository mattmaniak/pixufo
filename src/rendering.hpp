#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define CURRENT_DISPLAY 0
#define PIXELART_DISPLAY_WIDTH 720.0f

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

class Level;
class Background;
class Enemy;
class Menu;

class Rendering
{
	Uint32 frame_start_time;
	Uint32 frame_elapsed_time;
	Uint32 fps;

	public:
	bool            initialized;
	SDL_DisplayMode Display;
	SDL_Window*     Window;
	SDL_Renderer*   Renderer;
	float           delta_time; // A single frame period.

	Rendering();
	~Rendering();

	SDL_Texture* load_texture(const std::string name);
	float        pixelart_pixel_sz();
	void         start_fps_count();
	bool         count_fps();

	bool         tile_background(Background* Space);
	bool         render_level(Level* Level);
	bool         render_primary_menu(Menu* Menu);
	bool         render_pause_menu(Menu* Menu);
};

// namespace TODO
SDL_Surface* load_image(const std::string name);

#endif
