#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <random>
#include "sprite.hpp"

class Entity: public Sprite
{
public:
	int min_x;
	int max_x;
	int min_y;
	int max_y;

	const double          max_speed; // Pixel position move in a one second.
	double                step;      // Pixel position move in a one frame.
	std::vector<SDL_Rect> Hitbox_parts;

	Entity(Graphics&, const std::string, const double, const Uint32);

	void randomize_initial_pos();
	bool load_hitbox(Graphics&);
	bool render(Graphics&);
};

#endif
