#include "slowdown.hpp"
#include "player.hpp"

Player_slowdown::Player_slowdown(): max_time_s(1.0f)
{
	elapsed_horizontal_time_s = 0.0f;
	elapsed_vertical_time_s   = 0.0f;
}

void Player_slowdown::count_ratio(Graphics& Graphics, dir passed_direction)
{
	direction = passed_direction;

	switch(direction)
	{
		case left:
		if((elapsed_horizontal_time_s - Graphics.delta_time_s) >= -max_time_s)
		{
			elapsed_horizontal_time_s -= Graphics.delta_time_s;
		}
		break;

		case right:
		if((elapsed_horizontal_time_s + Graphics.delta_time_s) <= max_time_s)
		{
			elapsed_horizontal_time_s += Graphics.delta_time_s;
		}
		break;

		case up:
		if((elapsed_vertical_time_s - Graphics.delta_time_s) >= -max_time_s)
		{
			elapsed_vertical_time_s -= Graphics.delta_time_s;
		}
		break;

		case down:
		if((elapsed_vertical_time_s + Graphics.delta_time_s) <= max_time_s)
		{
			elapsed_vertical_time_s += Graphics.delta_time_s;
		}
	}
}

void Player_slowdown::move(Graphics& Graphics, Player& Ufo)
{
	switch(direction)
	{
		case left:
		case right:
		Ufo.horizontal_speed = Ufo.max_speed * (elapsed_horizontal_time_s
		                       / max_time_s);

		Ufo.step = Ufo.horizontal_speed * Graphics.delta_time_s
		           * Graphics.pixelart_px_sz();

		Ufo.pos_x += Ufo.step;
		break;

		case up:
		case down:
		Ufo.vertical_speed = Ufo.max_speed * (elapsed_vertical_time_s
		                     / max_time_s);

		Ufo.step = Ufo.vertical_speed * Graphics.delta_time_s
		           * Graphics.pixelart_px_sz();

		Ufo.pos_y += Ufo.step;
	}
}
