#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Model
{
	protected:
	SDL_Texture* Texture_;  // Driver-specific representation of data.

	public:
	bool         initialized;
	SDL_Rect     Geometry; // Texture_'s position and size.
	float        x;
	float        y;

	Model(Graphics* Graphics, const std::string name);
	~Model();

	bool render(Graphics* Graphics);
	int  count_scale();
};

class Planet: public Model
{
	float player_distance;
};

class Enemy: public Model
{
	public:
	float speed;
	float step;
	float max_x;
	float max_y;
	float player_distance;
};

class Player: public Model
{
	public:
	float speed;
	float step;

	Player(Graphics* Graphics, const std::string name, const float spd);
	bool render(Graphics* Graphics);
};

#endif
