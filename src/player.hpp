#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "model.hpp"

class Player_acceleration;
class Player_slowdown;

class Player: public Model
{
	public:
	Player_acceleration* Acceleration;
	Player_slowdown*     Slowdown;

	Player(Rendering* Rendering, const std::string name,
	       const float passed_max_speed);
	~Player();
};

#endif
