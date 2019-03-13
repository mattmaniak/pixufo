#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
#include "error.hpp"
#include "os_env.hpp"

#define CURRENT_DISPLAY_IDX 0
#define PIXELART_DISPLAY_WIDTH 640.0f

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

#define IMAGE_EXTENSION ".bmp"

class Level;
class Background;
class Enemy;
class Menus;
class Font;

class Graphics
{
public:
	double        delta_time_s;
	double        pixelart_px_sz;

	SDL_Rect      Display;
	SDL_Rect      Prev_display;

	SDL_Renderer* Renderer;

	Graphics();
	~Graphics();

	bool         set_up_new_frame();
	bool         count_fps();
	bool         render_primary_menu(Menus&);
	bool         render_pause_menu(Menus&, Level&);
	bool         clean_renderer();

private:
	bool renderer_initialized;
	bool window_initialized;

	SDL_Window* Window;
	Uint32      frame_start_time_ms;
	Uint32      frame_elapsed_time_ms;
	Uint32      fps;

	bool init_window();
	void         get_pixelart_px_sz();
	bool         render_font(Font&);
	bool         render_buttons(Menus&);
};

#endif
