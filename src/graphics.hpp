#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#include "error.hpp"

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
class Font;

class Graphics
{
	public:
	bool            is_initialized;
	float           delta_time_s;
	float           pixelart_px_sz;
	SDL_DisplayMode Display;
	SDL_Renderer*   Renderer;

	Graphics();
	~Graphics();

	SDL_Texture* load_texture(const std::string);
	bool         init_frame();
	bool         count_fps();
	bool         render_level(Level&, const bool);
	bool         render_primary_menu(Menu&);
	bool         render_pause_menu(Menu&, Level&);
	bool         clean_renderer();

	private:
	SDL_Window* Window;
	Uint32      frame_start_time_ms;
	Uint32      frame_elapsed_time_ms;
	Uint32      fps;

	SDL_Surface* load_image(const std::string);
	float        get_pixelart_px_sz();
	bool         render_tiled_background(Background&);
	bool         render_model(Model&);
	bool         render_font(Font&);
	bool         render_buttons(Menu&);
};

#endif
