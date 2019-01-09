#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

#define MIN_RESOLUTION_W 1280
#define MIN_RESOLUTION_H 720

class Window
{
	void _error(const std::string message);

	public:
	SDL_DisplayMode display;
	SDL_Window*     window;
	SDL_Renderer*   renderer;
	float           delta_time;
	float           frame_start_time;
	float           frame_elapsed_time;
	Uint32          fps;

	Window();
	~Window();

	SDL_Texture* create_texture(SDL_Surface* image);
	void count_fps();
	void quit();
};

#endif
