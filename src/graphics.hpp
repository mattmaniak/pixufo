#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#define CURRENT_DISPLAY 0
#define PIXELART_DISPLAY_WIDTH 640.0f

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

#define FILE_EXTENSION ".bmp"

class Level;
class Background;
class Enemy;
class Menu;
class Model;

class Graphics
{
	public:
	bool            is_initialized;
	SDL_DisplayMode Display;
	float           delta_time_s; // A single frame period.

	Graphics();
	~Graphics();

	SDL_Texture* load_texture(const std::string);
	float        pixelart_px_sz();
	void         start_fps_count();
	bool         count_fps();
	bool         render_level(Level*, const bool);
	bool         render_primary_menu(Menu*);
	bool         render_pause_menu(Menu*, Level*);
	bool         clean_renderer();

	private:
	SDL_Window*   Window;
	SDL_Renderer* Renderer;
	Uint32        frame_start_time_ms;
	Uint32        frame_elapsed_time_ms;
	Uint32        fps;

	SDL_Surface* load_image(const std::string);
	bool         render_tiled_background(Background*);
	bool         render_model(Model*);
	bool         render_buttons(Menu*);
};

#endif
