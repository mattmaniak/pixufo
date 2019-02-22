#ifndef SLOWDOWN_HPP
#define SLOWDOWN_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

class Player;

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
	bool is_active;
	dir  direction;

	Player_slowdown(const float passed_max_time);

	void activate(dir passed_direction);
	void deactivate();

	void fly(Player* Ufo);

	private:
	const float max_time;
	float       elapsed_time;
	float       start_time;

	float count_step_length(Player* Ufo);
};

#endif
