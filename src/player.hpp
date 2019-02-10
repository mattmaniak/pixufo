#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "model.hpp"

class Player_acceleration;
class Player_slowdown;

class Player: public Model
{
	public:
	Player_acceleration*            Acceleration;
	std::array<Player_slowdown*, 4> Slowdown;

	Player(Rendering* Rendering, const std::string name,
	       const float passed_max_speed);
	~Player();
};

#endif
