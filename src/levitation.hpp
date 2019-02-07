#ifndef LAVITATION_HPP
#define LEVITATION_HPP

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

// namespace model
// {
	class Player;
// }

class Levitation
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

	bool  levitate(Player* Ufo);
	float slowdown(Player* Ufo);
};

#endif
