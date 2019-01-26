#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Model_basic
{
	protected:
	SDL_Texture* Texture_;  // Driver-specific representation of data.

	public:
	bool         initialized;
	SDL_Rect     Geometry; // Texture_'s position and size.
	float        pos_x;
	float        pos_y;
	float        step;
	float        speed;

	Model_basic(Graphics* Graphics, const std::string name, const float spd);
	~Model_basic();

	bool render(Graphics* Graphics);
	int  count_scale();
};

class Model_planet: public Model_basic
{
	bool     visible;
	float    distance_to_player;
	SDL_Rect Hitbox;
};

class Model_enemy: public Model_basic // TODO: INHERIT FROM PLANET?
{
	public:
	bool     visible;
	float    distance_to_player;

	// float speed;
	// float step;

	Model_enemy(Graphics* Graphics, const std::string name, const float spd);
	bool render(Graphics* Graphics);
};

class Model_player: public Model_basic
{
	public:
	// float    speed;
	// float    step;

	Model_player(Graphics* Graphics, const std::string name, const float spd);
	bool render(Graphics* Graphics);
};

class Model_background: public Model_basic
{
	public:

	Model_background(Graphics* Graphics, const std::string name);

	bool tile(Graphics* Graphics);
};

class Model_button: public Model_basic
{
	public:
	const unsigned int index;

	Model_button(Graphics* Graphics, const std::string name, const int idx);

	bool render(Graphics* Graphics, unsigned int current_index);
};

#endif
