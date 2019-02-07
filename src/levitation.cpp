#include "levitation.hpp"
#include "model.hpp"
#include "player.hpp"

bool Levitation::levitate(Player* Ufo)
{
	elapsed_time = SDL_GetTicks() - Ufo->current_levitation_time;

	if(elapsed_time < Ufo->max_levitation_time)
	{
		if(elapsed_time > 0)
		{
			switch(last_direction)
			{
				case up:
				Ufo->pos_y -= slowdown(Ufo);
				break;

				case down:
				Ufo->pos_y += slowdown(Ufo);
				break;

				case left:
				Ufo->pos_x -= slowdown(Ufo);
				break;

				case right:
				Ufo->pos_x += slowdown(Ufo);
				break;

				case right_up:
				Ufo->step  /= std::sqrt(2.0f);
				Ufo->pos_x += slowdown(Ufo);
				Ufo->pos_y -= slowdown(Ufo);
				break;

				case right_down:
				Ufo->step /= std::sqrt(2.0f);
				Ufo->pos_x += slowdown(Ufo);
				Ufo->pos_y += slowdown(Ufo);
				break;

				case left_up:
				Ufo->step /= std::sqrt(2.0f);
				Ufo->pos_x -= slowdown(Ufo);
				Ufo->pos_y -= slowdown(Ufo);
				break;

				case left_down:
				Ufo->step /= std::sqrt(2.0f);
				Ufo->pos_x -= slowdown(Ufo);
				Ufo->pos_y += slowdown(Ufo);
			}
		}
	}
	else
	{
		Ufo->current_levitation_time = 0;
	}
	return true;
}

float Levitation::slowdown(Player* Ufo)
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
