#include "player.hpp"
#include "acceleration.hpp"
#include "slowdown.hpp"

Player::Player(Rendering* Rendering, const std::string name,
               const float passed_max_speed):
Model(Rendering, name, passed_max_speed)
{
	const float levitation_time = 1000.0f;

	Acceleration = new Player_acceleration(levitation_time);
	Slowdown     = new Player_slowdown(levitation_time);
}

Player::~Player()
{
	delete Acceleration;
	delete Slowdown;
}
