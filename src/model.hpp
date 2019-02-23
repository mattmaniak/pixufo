#ifndef MODELS_HPP
#define MODELS_HPP

#include <array>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include "error.hpp"
#include "graphics.hpp"

#define FRAMES_AMOUNT 6

class Model
{
	public:
	bool              is_initialized;
	const std::string name;

	std::array<SDL_Texture*, FRAMES_AMOUNT> Textures;
	std::size_t                             current_frame_idx;

	SDL_Rect    Geometry;  // Textures's position and size.
	const float max_speed; // Pixel position move in a one second.
	float       step;      // Pixel position move in a one frame.
	float       pos_x;     // Virtual Y-position to use with the delta time.
	float       pos_y;     // Virtual X-position to use with the delta time.

	// TODO: CONST?
	int min_x;
	int max_x;
	int min_y;
	int max_y;

	Model(Graphics*, const std::string, const float, const Uint32);
	~Model();

	void calc_pos(Graphics*);
	void animate(Graphics*);

	private:
	const Uint32 single_frame_time_ms;
	Uint32       frame_elapsed_time_ms;

	bool load_animation(Graphics*);
};

#endif
