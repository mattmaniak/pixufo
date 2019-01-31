#include "levitation.hpp"
#include "model.hpp"

bool Levitation::levitate(model::Player* Player)
{
	Uint32 elapsed_time = SDL_GetTicks() - Player->current_levitation_time;

	if(elapsed_time < Player->max_levitation_time)
	{
		Player->levitation = true;

		if(elapsed_time > 0)
		{
			switch(last_direction)
			{
				case up:
				Player->pos_y -= (Player->step / std::sqrt(std::sqrt(elapsed_time)));
				break;

				case down:
				Player->pos_y += (Player->step / std::sqrt(std::sqrt(elapsed_time)));
				break;

				case left:
				Player->pos_x -= (Player->step / std::sqrt(std::sqrt(elapsed_time)));
				break;

				case right:
				Player->pos_x += (Player->step / std::sqrt(std::sqrt(elapsed_time)));
				break;

				case right_up:
				Player->step /= std::sqrt(2);
				break;

				case right_down:
				Player->step /= std::sqrt(2);
				break;

				case left_up:
				Player->step /= std::sqrt(2);
				break;

				case left_down:
				Player->step /= std::sqrt(2);
			}
		}
	}
	else
	{
		Player->current_levitation_time = 0;
		Player->levitation = false;
	}
	return true;
}
