#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "model.hpp"

class Player_acceleration;
class Player_slowdown;

class Player: public Model
{
	public:
	std::array<Player_acceleration*, 4> Acceleration; // TODO: CAUSES UPWARD MOVE AT THE BEGINNING.
	std::array<Player_slowdown*, 4> Slowdown;

	Player(Rendering* Rendering, const std::string name,
	       const float passed_max_speed);
	~Player();
};

#endif
