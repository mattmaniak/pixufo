#include "slowdown.hpp"
#include "model.hpp"
#include "player.hpp"

Player_slowdown::Player_slowdown(const float passed_max_time):
                                 max_time(passed_max_time)
{

}

void Player_slowdown::set_direction(Player* Ufo)
{
	elapsed_time = SDL_GetTicks() - current_time;

	if(elapsed_time < max_time)
	{
		if(elapsed_time > 0.0f)
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
				Ufo->step /= std::sqrt(2.0f);
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
		elapsed_time = 0.0f;
	}
}

float Player_slowdown::count_step_length(Player* Ufo)
{
	/* Example mathemathical graph for that slowdown:
	f(x) = 1 / ((1000 - x) / 1000). */
	return Ufo->step * ((max_time - elapsed_time) / max_time);
}
