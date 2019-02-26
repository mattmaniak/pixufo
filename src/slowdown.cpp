#include "slowdown.hpp"
#include "player.hpp"

Player_slowdown::Player_slowdown(): max_time_s(0.4f)
{
	elapsed_time_s = 0.0f;
}

void Player_slowdown::count_ratio(Graphics& Graphics, dir passed_direction)
{
	direction = passed_direction;

	switch(direction)
	{
		case left:
		if((elapsed_time_s - Graphics.delta_time_s) >= -max_time_s)
		{
			elapsed_time_s -= Graphics.delta_time_s;
		}
		break;

		case right:
		if((elapsed_time_s + Graphics.delta_time_s) <= max_time_s)
		{
			elapsed_time_s += Graphics.delta_time_s;
		}
		break;

		case up:
		if((elapsed_time_s - Graphics.delta_time_s) >= -max_time_s)
		{
			elapsed_time_s -= Graphics.delta_time_s;
		}
		break;

		case down:
		if((elapsed_time_s + Graphics.delta_time_s) <= max_time_s)
		{
			elapsed_time_s += Graphics.delta_time_s;
		}
	}
}

void Player_slowdown::move(Graphics& Graphics, Player& Ufo)
{
	float vector_length = std::sqrt(std::pow(Ufo.horizontal_speed, 2.0f)
	                                + std::pow(Ufo.vertical_speed, 2.0f))
	                       / Ufo.max_speed;

	switch(direction)
	{
		case left:
		case right:
		Ufo.horizontal_speed = Ufo.max_speed * (elapsed_time_s / max_time_s);

		Ufo.horizontal_step = Ufo.horizontal_speed * Graphics.delta_time_s
		                      * Graphics.pixelart_px_sz;
		break;

		case up:
		case down:
		Ufo.vertical_speed = Ufo.max_speed * (elapsed_time_s / max_time_s);

		Ufo.vertical_step = Ufo.vertical_speed * Graphics.delta_time_s
		                    * Graphics.pixelart_px_sz;
	}

	// Prevents diagonal speed-ups.
	if((Ufo.directions_amount == 2) && (vector_length > 1.0f))
	{
		Ufo.horizontal_step /= vector_length;
		Ufo.vertical_step   /= vector_length;
	}
	switch(direction)
	{
		case left:
		case right:
		Ufo.pos_x += Ufo.horizontal_step;
		break;

		case up:
		case down:
		Ufo.pos_y += Ufo.vertical_step;
	}
}
