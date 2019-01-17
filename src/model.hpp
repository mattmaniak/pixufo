#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Model
{
	SDL_Texture* Texture_; // Driver-specific representation of data.

	public:
	bool     initialized;
	SDL_Rect Geometry; // Texture_'s position and size.
	float    speed;    // Pixels offset that can move in a one second.
	float    step;     // Real pixels per frame move.
	float    x;
	float    y;
	float    distance_to_player;
	int      max_x;
	int      max_y;

	Model(Graphics* Graphics, const std::string name, const float speed);
	~Model();

	bool render(Graphics* Graphics);
	int  count_scale();
};

#endif
