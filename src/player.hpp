#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "model.hpp"

class Player_slowdown;

#define DIRECTIONS_AMOUNT 4

class Player: public Model
{
	public:
	std::size_t current_slowdowns_amount;

	std::array<Player_slowdown*, DIRECTIONS_AMOUNT> Slowdowns;

	Player(Rendering* Rendering, const std::string name,
	       const float passed_max_speed);
	~Player();
};

#endif
