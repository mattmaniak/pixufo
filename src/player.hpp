#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>

#include "model.hpp"
#include "slowdown.hpp"

#define AXES_AMOUNT 2

class Player: public Model
{
	public:
	float horizontal_speed;
	float vertical_speed;

	std::array<Player_slowdown*, AXES_AMOUNT> Slowdowns;

	Player(Graphics&, const std::string, const float);
	~Player();
};

#endif
