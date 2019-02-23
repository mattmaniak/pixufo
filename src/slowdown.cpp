#include "slowdown.hpp"
#include "model.hpp"
#include "player.hpp"

Player_slowdown::Player_slowdown(const float passed_max_time_s):
                                 max_time_s(passed_max_time_s)
{
	elapsed_time_x_s = 0.0f;
	elapsed_time_y_s = 0.0f;
}

void Player_slowdown::activate(Graphics* Graphics, Player* Ufo, dir passed_direction)
{
	direction = passed_direction;

	switch(direction)
	{
		case left:
		if((elapsed_time_x_s + Graphics->delta_time_s) <= max_time_s)
		{
			elapsed_time_x_s += Graphics->delta_time_s;
		}
		Ufo->current_speed_x = Ufo->max_speed * (elapsed_time_x_s / max_time_s);
		break;

		case up:
		if((elapsed_time_y_s + Graphics->delta_time_s) <= max_time_s)
		{
			elapsed_time_y_s += Graphics->delta_time_s;
		}
		Ufo->current_speed_y = Ufo->max_speed * (elapsed_time_y_s / max_time_s);
		break;

		case right:
		if((elapsed_time_x_s - Graphics->delta_time_s) >= -max_time_s)
		{
			elapsed_time_x_s -= Graphics->delta_time_s;
		}
		Ufo->current_speed_x = Ufo->max_speed * (elapsed_time_x_s / max_time_s);
		break;

		case down:
		if((elapsed_time_y_s - Graphics->delta_time_s) >= -max_time_s)
		{
			elapsed_time_y_s -= Graphics->delta_time_s;
		}
		Ufo->current_speed_y = Ufo->max_speed * (elapsed_time_y_s / max_time_s);
	}
}

void Player_slowdown::fly(Player* Ufo, Graphics* Graphics)
{
	// Ufo->step = Ufo->current_speed * Graphics->delta_time_s * Graphics->pixelart_px_sz();

	switch(direction)
	{
		case up:
		case down:
		Ufo->step = Ufo->current_speed_y * Graphics->delta_time_s * Graphics->pixelart_px_sz();
		Ufo->pos_y -= Ufo->step;
		break;

		case left:
		case right:
		Ufo->step = Ufo->current_speed_x * Graphics->delta_time_s * Graphics->pixelart_px_sz();
		Ufo->pos_x -= Ufo->step;
	}
}
