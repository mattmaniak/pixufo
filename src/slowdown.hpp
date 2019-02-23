#ifndef SLOWDOWN_HPP
#define SLOWDOWN_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"

class Player;

enum axes
{
	horizontal,
	vertical
};

enum dir
{
	up,
	down,
	left,
	right
};

class Player_slowdown
{
	public:
	dir direction;
	const float max_time_s;
	float       elapsed_time_x_s;
	float       elapsed_time_y_s;

	Player_slowdown(const float);

	void activate(Graphics*, Player*, dir);
	void fly(Player*, Graphics*);
};

#endif
