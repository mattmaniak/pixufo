#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>

#include "model.hpp"

class Player_slowdown;

#define DIRECTIONS_AMOUNT 4

class Player: public Model
{
	public:
	std::array<Player_slowdown*, DIRECTIONS_AMOUNT> Slowdowns;
	SDL_Rect                                        Hitbox;

	Player(Graphics* Graphics, const std::string name,
	       const float passed_max_speed);
	~Player();
};

#endif
