#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>

#include "model.hpp"

class Player_slowdown;

#define AXES_AMOUNT 4

class Player: public Model
{
	public:
	float current_speed;

	std::array<Player_slowdown*, AXES_AMOUNT> Slowdowns;
	SDL_Rect                                  Hitbox;

	Player(Graphics* Graphics, const std::string name,
	       const float passed_max_speed);
	~Player();
};

#endif
