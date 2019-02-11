#ifndef SLOWDOWN_HPP
#define SLOWDOWN_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

class Player;

enum slowdown_direction
{
	slow_up,
	slow_down,
	slow_left,
	slow_right
};

class Player_slowdown
{
	public:
	slowdown_direction direction;

	bool        active;
	const float max_time;
	float       elapsed_time;
	float       current_time;

	Player_slowdown(const float passed_max_time);

	void  activate(slowdown_direction passed_direction);
	void  set_direction(Player* Ufo);
	float count_step_length(Player* Ufo);
};

#endif
