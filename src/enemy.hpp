#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "model.hpp"

class Enemy: public Model
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

	float distance_to_player;

	Enemy(Rendering* Rendering, const std::string name,
	      const float passed_max_speed);
};

#endif
