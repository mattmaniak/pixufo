#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "model.hpp"

class Player: public Model
{
	public:
	float current_speed;

	Player(Rendering* Rendering, const std::string name,
	       const float passed_max_speed);
};

#endif
