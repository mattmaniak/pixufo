#include "slowdown.hpp"
#include "model.hpp"
#include "player.hpp"

bool Slowdown::set_direction(Player* Ufo)
{
	elapsed_time = SDL_GetTicks() - Ufo->current_levitation_time;

	if(elapsed_time < Ufo->max_levitation_time)
	{
		if(elapsed_time > 0)
		{
			switch(last_direction)
			{
				case up:
				Ufo->pos_y -= count_step_length(Ufo);
				break;

				case down:
				Ufo->pos_y += count_step_length(Ufo);
				break;

				case left:
				Ufo->pos_x -= count_step_length(Ufo);
				break;

				case right:
				Ufo->pos_x += count_step_length(Ufo);
				break;

				case right_up:
				Ufo->step  /= std::sqrt(2.0f);
				Ufo->pos_x += count_step_length(Ufo);
				Ufo->pos_y -= count_step_length(Ufo);
				break;

				case right_down:
				Ufo->step /= std::sqrt(2.0f);
				Ufo->pos_x += count_step_length(Ufo);
				Ufo->pos_y += count_step_length(Ufo);
				break;

				case left_up:
				Ufo->step /= std::sqrt(2.0f);
				Ufo->pos_x -= count_step_length(Ufo);
				Ufo->pos_y -= count_step_length(Ufo);
				break;

				case left_down:
				Ufo->step /= std::sqrt(2.0f);
				Ufo->pos_x -= count_step_length(Ufo);
				Ufo->pos_y += count_step_length(Ufo);
			}
		}
	}
	else
	{
		Ufo->current_levitation_time = 0;
	}
	return true;
}

float Slowdown::count_step_length(Player* Ufo)
{
	/* Increment for slowdown. Just dynamic change of the step each time. Looks
	very ugly but scales the speed naturally. */
	float exponent = (Ufo->max_levitation_time / 20.0f)
	                 / (Ufo->max_levitation_time - elapsed_time);

	if(exponent > 1.0f)
	{
		exponent = 1.0f;
	}

	// Example mathemathical graph for that slowdown: f(x) = 1 / x^exponent.
	return Ufo->step / std::pow(elapsed_time, exponent);
}
