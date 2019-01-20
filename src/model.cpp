#include "model.hpp"
#include "graphics.hpp"

Model::Model(Graphics* Graphics, const std::string name)
{
	Texture_ = Graphics->load_texture(name);
	if(Texture_ == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		initialized = false;
		return;
	}

	if(SDL_QueryTexture(Texture_, nullptr, nullptr, &Geometry.w, &Geometry.h)
	   != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		initialized = false;
		return;
	}

	Geometry.w *= count_scale();
	Geometry.h *= count_scale();
	Geometry.x  = pos_x = 0.0f;
	Geometry.y  = pos_y = 0.0f;

	initialized = true;
}

Model::~Model()
{
	if(Texture_ != nullptr)
	{
		SDL_DestroyTexture(Texture_);
	}
}

bool Model::render(Graphics* Graphics)
{
	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

int Model::count_scale()
{
	const int       pixelart_display_width = 480;
	const int       display_index = 0;
	SDL_DisplayMode Current_display;

	SDL_GetCurrentDisplayMode(display_index, &Current_display);

	return (Current_display.w / pixelart_display_width);
}

Player::Player(Graphics* Graphics, const std::string name, const float spd)
: Model(Graphics, name)
{
	speed = spd;

	Geometry.x = (Graphics->Display.w - Geometry.w) / 2;
	Geometry.y = (Graphics->Display.h - Geometry.h) / 2;

	Hitbox.w = Geometry.w / 2;
	Hitbox.h = Geometry.h / 2;
	Hitbox.x = (Graphics->Display.w - Hitbox.w) / 2;
	Hitbox.y = (Graphics->Display.h - Hitbox.h) / 2;
}

bool Player::render(Graphics* Graphics)
{
	step = speed * Graphics->delta_time * count_scale();

	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

Enemy::Enemy(Graphics* Graphics, const std::string name, const float spd)
: Model(Graphics, name)
{
	speed = spd;
	pos_x = 0;
	pos_y = 0;
}

bool Enemy::render(Graphics* Graphics)
{
	step = speed * Graphics->delta_time * count_scale();

	Geometry.x = pos_x;
	Geometry.y = pos_y;

	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

Background::Background(Graphics* Graphics, const std::string name)
: Model(Graphics, name)
{

}

bool Background::tile(Graphics* Graphics)
{
	// Additional value to support the infinite scrolling.
	unsigned int tiles_x = (Graphics->Display.w / Geometry.w) + 1;
	unsigned int tiles_y = (Graphics->Display.h / Geometry.h) + 1;

	if(pos_x > 0) // Shifted right.
	{
		pos_x -= Geometry.w; // Shift the background one tile left.
	}
	else if(pos_x < -Geometry.w) // Shifted left.
	{
		pos_x += Geometry.w; // Shift the background one tile right.
	}
	if(pos_y > 0) // Shifted down.
	{
		pos_y -= Geometry.h; // Shift the background one tile up.
	}
	else if(pos_y < -Geometry.h) // Shifted up.
	{
		pos_y += Geometry.h; // Shift the background one tile down.
	}

	for(unsigned int y = 0; y <= tiles_y; y++)
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Geometry.x = pos_x + (x * Geometry.w);
			Geometry.y = pos_y + (y * Geometry.h);

			if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
			{
				std::cerr << SDL_GetError() << std::endl;
				return false;
			}
		}
	}
	return true;
}
