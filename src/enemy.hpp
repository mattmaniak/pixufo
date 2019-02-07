#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "model.hpp"

class Enemy: public Model
{
	public:
	bool     visible;
	float    distance_to_player;

	Enemy(Graphics* Graphics, const std::string name, const float speed);
};

#endif
