#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

#define MIN_RESOLUTION_W 1024
#define MIN_RESOLUTION_H 576

class Graphics
{
	float        frame_start_time;
	float        frame_elapsed_time;
	unsigned int fps;

	public:
	bool            initialized;
	SDL_DisplayMode Display;
	SDL_Window*     Window;
	SDL_Renderer*   Renderer;
	float           delta_time;

	Graphics();
	~Graphics();

	SDL_Texture* load_texture(const std::string name);
	bool         render(void* Model_basic);
	void         count_frame_start_time();
	bool         count_elapsed_time();
};

SDL_Surface* load_image(const std::string name);

#endif
