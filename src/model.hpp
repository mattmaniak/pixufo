#ifndef MODELS_HPP
#define MODELS_HPP

#include <array>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include "error.hpp"
#include "graphics.hpp"

#define MAX_FRAMES_AMOUNT 6

class Model
{
	public:
	bool              initialized;
	const std::string name;

	bool              animated;
	Uint32            animation_period;
	std::size_t       current_frame_idx;
	Uint32            animation_elapsed_time;

	std::array<SDL_Texture*, MAX_FRAMES_AMOUNT> Textures;

	// SDL_Texture*      Textures;  // Driver-specific representation of data.
	SDL_Rect          Geometry; // Textures's position and size.

	const float       speed;    // Pixel position move in a one second.
	float             step;     // Pixel position move in a one frame.
	float             pos_x;    // Virtual Y-position to use with a delta.
	float             pos_y;    // Virtual X-position to use with a delta.

	// TODO: CONST?
	int               min_x;
	int               max_x;
	int               min_y;
	int               max_y;

	Model(Graphics* Graphics, const std::string passed_name,
	      const float passed_speed, const bool passed_animated);
	~Model();

	void convert_pos();
	bool load_animation_files(Graphics* Graphics);
	void animate(Graphics* Graphics);
};

#endif
