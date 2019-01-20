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
	float        pos_x;
	float        pos_y;

	Model(Graphics* Graphics, const std::string name);
	~Model();

	bool render(Graphics* Graphics);
	int  count_scale();
};

class Planet: public Model
{
	bool     visible;
	float    distance_to_player;
	SDL_Rect Hitbox;
};

class Enemy: public Model // TODO: INHERIT FROM PLANET?
{
	public:
	bool     visible;
	float    distance_to_player;
	SDL_Rect Hitbox;

	float speed;
	float step;
	// float max_x;
	// float max_y;

	Enemy(Graphics* Graphics, const std::string name, const float spd);
	bool render(Graphics* Graphics);
};

class Player: public Model
{
	public:
	float    speed;
	float    step;
	SDL_Rect Hitbox;

	Player(Graphics* Graphics, const std::string name, const float spd);
	bool render(Graphics* Graphics);
};

class Background: public Model
{
	public:

	Background(Graphics* Graphics, const std::string name);
	bool tile(Graphics* Graphics);
};

#endif
