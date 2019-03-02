#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include <cmath>

#include "sprite.hpp"
#include "graphics.hpp"

#define AXES_AMOUNT 2

class Player_movement;

class Player: public Sprite
{
	public:
	double horizontal_speed;
	double vertical_speed;

	double horizontal_step;
	double vertical_step;

	std::size_t directions_amount;

	std::array<Player_movement*, AXES_AMOUNT> Movement;

	Player(Graphics&);
	~Player();
};

enum axis
{
	horizontal,
	vertical
};

enum dir
{
	left,
	right,
	up,
	down
};

class Player_movement
{
	public:
	dir          direction;
	const double max_time_s;
	double       elapsed_time_s;

	Player_movement();

	void count_ratio(Graphics&, dir);
	void move(Graphics&, Player&);
};

#endif
