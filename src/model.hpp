#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include "error.hpp"
#include "graphics.hpp"

class Model
{
	public:
	const std::string name;
	bool              initialized;

	SDL_Texture*      Texture;  // Driver-specific representation of data.
	SDL_Rect          Geometry; // Texture's position and size.

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
	      const float passed_speed);
	~Model();

	void convert_pos();
};

#endif
