#include "acceleration.hpp"
#include "player.hpp"

Player_acceleration::Player_acceleration(const float passed_max_time):
                                         active(false), max_time(passed_max_time)
{

}

void Player_acceleration::set_direction(Player* Ufo)
{
	elapsed_time = SDL_GetTicks() - current_time;

	if(elapsed_time < max_time)
	{
		if(elapsed_time > 0.0f)
		{

		}
	}
	else
	{
		elapsed_time = 0.0f;
	}
}

float Player_acceleration::count_step_length(Player* Ufo)
{
	/* Example mathemathical graph for that slowdown:
	f(x) = 1 / ((1000 - x) / 1000). */
	return Ufo->step * ((max_time - elapsed_time) / max_time);
}
