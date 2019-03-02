#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "error.hpp"
#include "graphics.hpp"
#include "os.hpp"

#define FRAMES_AMOUNT 6

class Sprite
{
	public:
	bool              is_initialized;
	const std::string name;
	std::string       path;

	std::array<SDL_Texture*, FRAMES_AMOUNT> Textures;
	std::size_t                             current_frame_idx;

	SDL_Rect     Geometry;  // Textures's position and size.
	const double max_speed; // Pixel position move in a one second.
	double       step;      // Pixel position move in a one frame.
	double       pos_x;     // Virtual Y-position to use with the delta time.
	double       pos_y;     // Virtual X-position to use with the delta time.

	std::vector<SDL_Rect> Hitbox_parts;

	int min_x;
	int max_x;
	int min_y;
	int max_y;

	Sprite(Graphics&, const std::string, const double, const Uint32);
	~Sprite();

	bool load_hitbox();
	void move(Graphics&, const double, const double);
	void animate(const Graphics&);
	bool render(Graphics&);

	private:
	const Uint32 single_frame_time_ms;
	Uint32       frame_elapsed_time_ms;

	void calc_pos(Graphics&);
	bool load_animation(Graphics&);
};

#endif
