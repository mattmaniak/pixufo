#ifndef SLOWDOWN_HPP
#define SLOWDOWN_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

class Player;

class Slowdown
{
	public:
	enum
	{
		up,
		down,
		left,
		right,
		right_up,
		right_down,
		left_up,
		left_down
	}
	last_direction;

	float elapsed_time;

	bool  set_direction(Player* Ufo);
	float count_step_length(Player* Ufo);
};

#endif
