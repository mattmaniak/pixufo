#include "acceleration.hpp"
#include "player.hpp"

Player_acceleration::Player_acceleration(const float passed_max_time):
                                         max_time(passed_max_time)
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
