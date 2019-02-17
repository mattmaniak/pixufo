#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "level.hpp"
#include "entity.hpp"

namespace physics
{
	void check_model_pos(Model* Model);
	void move_enemies(Level* Level);
}

#endif
