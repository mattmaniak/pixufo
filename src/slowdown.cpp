#include "slowdown.hpp"
#include "model.hpp"
#include "player.hpp"

Player_slowdown::Player_slowdown(const float passed_max_time):
                                 max_time(passed_max_time)
{

}

void Player_slowdown::activate(dir passed_direction)
{
	is_active  = true;
	start_time = SDL_GetTicks();
	direction  = passed_direction;
}

void Player_slowdown::deactivate()
{
	is_active    = false;
	elapsed_time = max_time;
}

void Player_slowdown::fly(Player* Ufo)
{
	if(is_active)
	{
		elapsed_time = SDL_GetTicks() - start_time;

		if((elapsed_time > 0.0f) && (elapsed_time < max_time))
		{
			switch(direction)
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
			}
		}
	}
}

float Player_slowdown::count_step_length(Player* Ufo)
{
	/* Example mathemathical graph for that slowdown:
	f(x) = 1 / ((1000 - x) / 1000). */
	return Ufo->step * ((max_time - elapsed_time) / max_time);
}
