#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

class Level;
class Background;
class Enemy;

class Graphics
{
	float  frame_start_time;
	float  frame_elapsed_time;
	Uint32 fps;

	public:
	bool            initialized;
	SDL_DisplayMode Screen;
	SDL_Window*     Window;
	SDL_Renderer*   Renderer;
	float           delta_time; // A single frame period.

	Graphics();
	~Graphics();

	SDL_Texture* load_texture(const std::string name);
	void         start_fps_count();
	bool         count_fps();
	bool         tile_background(Background* Space);
	bool         render_level(Level* Level);
};

SDL_Surface* load_image(const std::string name);

#endif
