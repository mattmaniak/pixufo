#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

#define PIXELART_DISPLAY_WIDTH 640

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
	float           delta_time;

	Graphics();
	~Graphics();

	SDL_Texture* load_texture(const std::string name);
	bool         count_frame_start_time();
	bool         count_elapsed_time();

	template<class Model>
	bool render(Model* Model_to_render);
};

SDL_Surface* load_image(const std::string name);

#endif
