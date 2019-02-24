#ifndef SLOWDOWN_HPP
#define SLOWDOWN_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

#include "graphics.hpp"

class Player;

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

class Player_slowdown
{
	public:
	dir         direction;
	const float max_time_s;
	float       elapsed_time_s;

	Player_slowdown();

	void count_ratio(Graphics&, dir);
	void move(Graphics&, Player&);
};

#endif
