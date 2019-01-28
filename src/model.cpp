#include "model.hpp"
#include "error.hpp"
#include "graphics.hpp"

model::Basic::Basic(Graphics* Graphics, const std::string name,
                         const float spd): speed(spd)
{
	Texture_ = Graphics->load_texture(name);
	if(Texture_ == nullptr)
	{
		initialized = false;
		return;
	}

	if(SDL_QueryTexture(Texture_, nullptr, nullptr, &Geometry.w, &Geometry.h)
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

	initialized = true;
}

model::Basic::~Basic()
{
	if(Texture_ != nullptr)
	{
		SDL_DestroyTexture(Texture_);
	}
}

bool model::Basic::render(Graphics* Graphics)
{
	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't copy a texture to the renderer."); // TODO: WITH PATH
		return false;
	}
	return true;
}

float model::Basic::count_scale()
{
	const int       display_index = 0;
	SDL_DisplayMode Ingame_display;

	if(SDL_GetDesktopDisplayMode(display_index, &Ingame_display) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the current display size.");
		initialized = false;
	}
	return Ingame_display.w / PIXELART_DISPLAY_WIDTH;
}

model::Player::Player(Graphics* Graphics, const std::string name,
                      const float speed):
model::Basic(Graphics, name, speed)
{
	step = 0.0f;

	Geometry.x = pos_x = (Graphics->Screen.w - Geometry.w) / 2;
	Geometry.y = pos_y = (Graphics->Screen.h - Geometry.h) / 2;
}

bool model::Player::render(Graphics* Graphics)
{
	step = speed * Graphics->delta_time * count_scale();

	Geometry.x = pos_x;
	Geometry.y = pos_y;

	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		error::show_box("Can't copy a texture to the renderer.");
		return false;
	}
	return true;
}

model::Enemy::Enemy(Graphics* Graphics, const std::string name,
                    const float speed):
model::Basic(Graphics, name, speed)
{
	pos_x = pos_y = 0.0f;
}

bool model::Enemy::render(Graphics* Graphics)
{
	step = speed * Graphics->delta_time * count_scale();

	Geometry.x = pos_x;
	Geometry.y = pos_y;

	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		error::show_box("Can't copy a texture to the renderer.");
		return false;
	}
	return true;
}

model::Background::Background(Graphics* Graphics, const std::string name):
model::Basic(Graphics, name, 0.0f)
{

}

bool model::Background::tile(Graphics* Graphics)
{
	// Additional row and column to support the infinite scrolling.
	unsigned int tiles_x = Graphics->Screen.w / Geometry.w;
	unsigned int tiles_y = Graphics->Screen.h / Geometry.h;

	if((tiles_x >= std::numeric_limits<unsigned int>::max())
	|| (tiles_y >= std::numeric_limits<unsigned int>::max()))
	{
		error::show_box("Too many tiles in the background.");
		return false;
	}

	// Scrolling. TODO: DOESN"T WORK.
	// if(pos_x > 0) // Background shifted right.
	// {
	// 	pos_x -= Geometry.w; // Move the background one tile left.
	// }
	// else if(pos_x < -Geometry.w) // Background shifted left.
	// {
	// 	pos_x += Geometry.w; // Move the background one tile right.
	// }
	// if(pos_y > 0) // Background shifted down.
	// {
	// 	pos_y -= Geometry.h; // Move the background one tile up.
	// }
	// else if(pos_y < -Geometry.h) // Background shifted up.
	// {
	// 	pos_y += Geometry.h; // Move the background one tile down.
	// }
	// std::cout << "Background: " << pos_x << ' ' << pos_y << std::endl;

	// Tiling.
	for(unsigned int y = 0; y <= tiles_y; y++)
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Geometry.x = pos_x + (x * Geometry.w);
			Geometry.y = pos_y + (y * Geometry.h);

			if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry)
			!= SDL2_SUCCESS)
			{
				error::show_box("Can't copy a texture to the renderer.");
				return false;
			}
		}
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
	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		error::show_box("Can't copy a texture to the renderer.");
		return false;
	}
	return true;
}
