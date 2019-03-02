#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>

#include "error.hpp"
#include "os.hpp"

#define CURRENT_DISPLAY_IDX 0
#define PIXELART_DISPLAY_WIDTH 480.0f

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

#define FILE_EXTENSION ".bmp"

class Level;
class Background;
class Enemy;
class Menu;
class Font;

class Graphics
{
	public:
	bool            is_initialized;
	double          delta_time_s;
	double          pixelart_px_sz;

	SDL_Rect        Display;
	SDL_Rect        Prev_display;

	SDL_Renderer*   Renderer;

	Graphics();
	~Graphics();

	SDL_Texture* load_texture(const std::string);
	bool         init_frame(Level& Level);
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
	bool         get_pixelart_px_sz();
	bool         render_font(Font&);
	bool         render_buttons(Menu&);
};

#endif
