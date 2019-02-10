#include "player.hpp"
#include "acceleration.hpp"
#include "slowdown.hpp"

Player::Player(Rendering* Rendering, const std::string name,
               const float passed_max_speed):
Model(Rendering, name, passed_max_speed)
{
	const float levitation_time = 3000.0f;

	Acceleration = new Player_acceleration(levitation_time);

	for(std::size_t dir_idx = 0; dir_idx < 4; dir_idx++)
	{
		Slowdown[dir_idx] = new Player_slowdown(levitation_time);
	}
}

Player::~Player()
{
	delete Acceleration;

	for(std::size_t dir_idx = 0; dir_idx < 4; dir_idx++)
	{
		delete Slowdown[dir_idx];
	}
}
