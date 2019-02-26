#include "player.hpp"

Player::Player(Graphics& Graphics): Model(Graphics, "ufo", 150.0, 0)
{
	horizontal_speed = 0.0;
	vertical_speed   = 0.0;

	horizontal_step = 0.0;
	vertical_step   = 0.0;

	directions_amount = 0;

	for(std::size_t axis_idx = 0; axis_idx < AXES_AMOUNT; axis_idx++)
	{
		Slowdowns[axis_idx] = new Player_movement;
	}
}

Player::~Player()
{
	for(std::size_t axis_idx = 0; axis_idx < AXES_AMOUNT; axis_idx++)
	{
		delete Slowdowns[axis_idx];
	}
}

Player_movement::Player_movement(): max_time_s(0.4)
{
	elapsed_time_s = 0.0;
}

void Player_movement::count_ratio(Graphics& Graphics, dir passed_direction)
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

void Player_movement::move(Graphics& Graphics, Player& Ufo)
{
	double vector_length = std::sqrt(std::pow(Ufo.horizontal_speed, 2.0)
	                                + std::pow(Ufo.vertical_speed, 2.0))
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
	if((Ufo.directions_amount == 2) && (vector_length > 1.0))
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
