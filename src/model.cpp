#include "model.hpp"
#include "error.hpp"
#include "graphics.hpp"

model::Basic::Basic(Graphics* Graphics, const std::string name,
                    const float spd): speed(spd)
{
	Texture = Graphics->load_texture(name);
	if(Texture == nullptr)
	{
		initialized = false;
		return;
	}

	if(SDL_QueryTexture(Texture, nullptr, nullptr, &Geometry.w, &Geometry.h)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get a texture size.");
		initialized = false;
		return;
	}

	Geometry.w *= count_scale();
	Geometry.h *= count_scale();
	Geometry.x  = pos_x = 0.0f;
	Geometry.y  = pos_y = 0.0f;

	step = 0.0f;

	initialized = true;
}

model::Basic::~Basic()
{
	if(Texture != nullptr)
	{
		SDL_DestroyTexture(Texture);
	}
}

float model::Basic::count_scale()
{
	const int       display_index = 0;
	SDL_DisplayMode Ingame_display;

	if(SDL_GetDesktopDisplayMode(display_index, &Ingame_display)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get the current display size.");
		initialized = false;
	}
	return Ingame_display.w / PIXELART_DISPLAY_WIDTH;
}

model::Enemy::Enemy(Graphics* Graphics, const std::string name,
                    const float speed):
model::Basic(Graphics, name, speed)
{
	pos_x = pos_y = 0.0f;
}

model::Background::Background(Graphics* Graphics, const std::string name):
model::Basic(Graphics, name, 0.0f)
{

}

model::Player::Player(Graphics* Graphics, const std::string name, const float spd):
model::Basic(Graphics, name, spd), max_levitation_time(1000), current_levitation_time(0)
{

}

bool model::Player::count_levitation_time(Graphics* Graphics)
{
	// current_levitation_time = SDL_GetTicks(); // TODO: MAX VALUES CHECKS.

	if((SDL_GetTicks() - current_levitation_time) < max_levitation_time)
	{
		// step = speed * count_scale() * Graphics->delta_time;

		pos_y -= step;

		if(pos_y <= -(Geometry.h - count_scale()))
		{
			pos_y = Graphics->Screen.h - count_scale();
		}
	}
	else
	{
		current_levitation_time = 0;
	}
	return true;
}


model::Button::Button(Graphics* Graphics, const std::string name,
                      const int idx):
model::Basic(Graphics, name, 0.0f), index(idx)
{

}

bool model::Button::render(Graphics* Graphics, unsigned int current_index)
{
	const unsigned int actual_button_shift = 64;

	// Centering.
	Geometry.x = (Graphics->Screen.w - Geometry.w) / 2;
	Geometry.y = (Graphics->Screen.h / 2) + (index * Geometry.h);

	// Selected button shift.
	if(index == current_index)
	{
		Geometry.x += actual_button_shift;
	}
	if(SDL_RenderCopy(Graphics->Renderer, Texture, NULL, &Geometry) != 0)
	{
		error::show_box("Can't copy a texture to the renderer.");
		return false;
	}
	return true;
}
