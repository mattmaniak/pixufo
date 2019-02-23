#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>

#include "model.hpp"

class Player_slowdown;

#define AXES_AMOUNT 4

class Player: public Model
{
	public:
	float horizontal_speed;
	float vertical_speed;
	float horizontal_step;
	float vertical_step;

	std::array<Player_slowdown*, AXES_AMOUNT> Slowdowns;
	SDL_Rect                                  Hitbox;

	Player(Graphics*, const std::string, const float);
	~Player();
};

#endif
