#include "player.hpp"

Player::Player(Graphics& Graphics, const std::string name,
               const float passed_max_speed):
Model(Graphics, name, passed_max_speed, 0)
{
	horizontal_speed = 0.0f;
	vertical_speed   = 0.0f;

	for(std::size_t axis_idx = 0; axis_idx < AXES_AMOUNT; axis_idx++)
	{
		Slowdowns[axis_idx] = new Player_slowdown;
	}
}

Player::~Player()
{
	for(std::size_t axis_idx = 0; axis_idx < AXES_AMOUNT; axis_idx++)
	{
		delete Slowdowns[axis_idx];
	}
}
