#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "model.hpp"

class Entity: public Model
{
	public:
	enum
	{
		up,
		down,
		left,
		right,

		right_up,
		right_down,
		left_down,
		left_up
	}
	direction;

	SDL_Rect Hitbox;

	Entity(Graphics* Graphics, const std::string name,
	      const float passed_speed);

	void randomize_initial_pos();
};

#endif