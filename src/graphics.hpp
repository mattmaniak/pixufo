#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

#define MIN_RESOLUTION_W 1024
#define MIN_RESOLUTION_H 576

class Graphics
{
	float  frame_elapsed_time;
	float  frame_start_time;
	Uint32 fps;

	void _error();

	public:
	SDL_DisplayMode Screen;
	SDL_Window*     Window;
	SDL_Renderer*   Renderer;
	float           delta_time;

	Graphics();
	~Graphics();

	SDL_Texture* create_texture(SDL_Surface* image);
	int          render();
	void         count_frame_start_time();
	int          count_elapsed_time();
	void         destroy();
};

#endif
