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

	float horizontal_step;
	float vertical_step;

	std::size_t directions_amount;

	std::array<Player_slowdown*, AXES_AMOUNT> Slowdowns;

	Player(Graphics&, const std::string, const float);
	~Player();
};

#endif
