#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "level.hpp"
#include "graphics.hpp"

namespace physics
{
	void check_model_pos(Sprite&);
	bool check_player_collision(Graphics&, Level&);
}

#endif
