#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <random>
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

	Entity(Graphics*, const std::string, const float, const Uint32);

	void randomize_initial_pos();
};

#endif
