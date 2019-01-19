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
	Geometry.x  = x = 0.0f;
	Geometry.y  = y = 0.0f;

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
}

bool Player::render(Graphics* Graphics)
{
	step = speed * Graphics->delta_time * count_scale();

	Geometry.x = x;
	Geometry.y = y;

	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}
