#include "acceleration.hpp"
#include "player.hpp"

Player_acceleration::Player_acceleration(const float passed_max_time):
                                         active(false), max_time(passed_max_time)
{

}

void Player_acceleration::activate(acceleration_direction passed_direction)
{
	active       = true;
	current_time = SDL_GetTicks();
	direction    = passed_direction;
}

void Player_acceleration::set_direction(Player* Ufo)
{
	elapsed_time = SDL_GetTicks() - current_time;

	if(elapsed_time < max_time)
	{
		if(elapsed_time > 0.0f)
		{
			switch(direction)
			{
				case acc_up:
				Ufo->pos_y += count_step_length(Ufo);
				break;

				case acc_down:
				Ufo->pos_y -= count_step_length(Ufo);
				break;

				case acc_left:
				Ufo->pos_x += count_step_length(Ufo);
				break;

				case acc_right:
				Ufo->pos_x -= count_step_length(Ufo);
			}
		}
	}
	else
	{
		elapsed_time = 0.0f;
		active       = false;
	}
}

float Player_acceleration::count_step_length(Player* Ufo)
{
	/* Example mathemathical graph for that slowdown:
	f(x) = 1 / ((1000 - x) / 1000). */
	return Ufo->step * ((max_time - elapsed_time) / max_time);
}
