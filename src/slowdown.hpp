#ifndef SLOWDOWN_HPP
#define SLOWDOWN_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

class Player;

class Player_slowdown
{
	public:
	enum direction
	{
		up,
		down,
		left,
		right,
	}
	last_direction;

	const float max_time;
	float       elapsed_time;
	float       current_time;

	Player_slowdown(const float passed_max_time);

	void  activate(direction last_dir);
	void  set_direction(Player* Ufo);
	float count_step_length(Player* Ufo);
};

#endif
