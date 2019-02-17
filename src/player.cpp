#include "player.hpp"
#include "slowdown.hpp"

Player::Player(Graphics* Graphics, const std::string name,
               const float passed_max_speed):
Model(Graphics, name, passed_max_speed, false)
{
	for(std::size_t dir_idx = 0; dir_idx < 4; dir_idx++)
	{
		Slowdowns[dir_idx] = new Player_slowdown(2000.0f);
	}
}

Player::~Player()
{
	for(std::size_t dir_idx = 0; dir_idx < 4; dir_idx++)
	{
		delete Slowdowns[dir_idx];
	}
}
