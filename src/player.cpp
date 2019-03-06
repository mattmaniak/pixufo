#include "player.hpp"

Player::Player(Graphics& Graphics): Entity(Graphics, "ufo", 100.0, 0),
               keys(SDL_GetKeyboardState(nullptr))
{
	horizontal_speed = 0.0;
	vertical_speed   = 0.0;
	horizontal_step  = 0.0;
	vertical_step    = 0.0;

	directions_amount = 0;

	Movements.insert(std::make_pair("horizontal", new player::Movement));
	Movements.insert(std::make_pair("vertical", new player::Movement));
}

Player::~Player()
{
	Movements.erase("horizontal");
	Movements.erase("vertical");
}

bool Player::keyboard_steering(Menu& Menu, Graphics& Graphics)
{
	directions_amount = 0;

	SDL_PollEvent(&Event);
	switch(Event.type)
	{
		case SDL_QUIT:
		return false;
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		Movements["horizontal"]->count_ratio(Graphics, left);
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		Movements["horizontal"]->count_ratio(Graphics, right);
	}
	if(keys[SDL_SCANCODE_UP])
	{
		Movements["vertical"]->count_ratio(Graphics, up);
	}
	if(keys[SDL_SCANCODE_DOWN])
	{
		Movements["vertical"]->count_ratio(Graphics, down);
	}
	if(keys[SDL_SCANCODE_ESCAPE])
	{
		Menu.mode = Menu.pause_enabled;
	}

	if((horizontal_speed != 0.0f) && (vertical_speed != 0.0f))
	{
		directions_amount = 2;
	}
	Movements["horizontal"]->move(Graphics, *this);
	Movements["vertical"]->move(Graphics, *this);

	return true;
}

player::Movement::Movement(): max_time_s(0.4)
{
	elapsed_time_s = 0.0;
}

void player::Movement::count_ratio(Graphics& Graphics, dir passed_direction)
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

void player::Movement::move(Graphics& Graphics, Player& Ufo)
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
