#include "levitation.hpp"
#include "model.hpp"

bool Levitation::levitate(model::Player* Player)
{
	elapsed_time = SDL_GetTicks() - Player->current_levitation_time;

	if(elapsed_time < Player->max_levitation_time)
	{
		if(elapsed_time > 0)
		{
			switch(last_direction)
			{
				case up:
				Player->pos_y -= slowdown(Player);
				break;

				case down:
				Player->pos_y += slowdown(Player);
				break;

				case left:
				Player->pos_x -= slowdown(Player);
				break;

				case right:
				Player->pos_x += slowdown(Player);
				break;

				case right_up:
				Player->step  /= std::sqrt(2.0f);
				Player->pos_x += slowdown(Player);
				Player->pos_y -= slowdown(Player);
				break;

				case right_down:
				Player->step /= std::sqrt(2.0f);
				Player->pos_x += slowdown(Player);
				Player->pos_y += slowdown(Player);
				break;

				case left_up:
				Player->step /= std::sqrt(2.0f);
				Player->pos_x -= slowdown(Player);
				Player->pos_y -= slowdown(Player);
				break;

				case left_down:
				Player->step /= std::sqrt(2.0f);
				Player->pos_x -= slowdown(Player);
				Player->pos_y += slowdown(Player);
			}
		}
	}
	else
	{
		Player->current_levitation_time = 0;
	}
	return true;
}

float Levitation::slowdown(model::Player* Player)
{
	const float exponent = 0.2f;

	// Mathemathical graph for that slowdown: f(x) = 1 / x^exponent.

	return Player->step / std::pow(elapsed_time, exponent);
}
