#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "model.hpp"

class Enemy: public Model
{
	public:
	float distance_to_player;

	Enemy(Rendering* Rendering, const std::string name, const float speed);
};

#endif
