#include "model.hpp"
#include "graphics.hpp"

Model::Model(Graphics* Graphics, const std::string name, const float spd)
: speed(spd)
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

	max_x = Graphics->Display.w; // TEMPONARY.
	max_y = Graphics->Display.h; // TOO.

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
	step = speed * count_scale() * Graphics->delta_time;

	Geometry.x = x;
	Geometry.y = y;

	if(SDL_RenderCopy(Graphics->Renderer, Texture_, NULL, &Geometry) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

int Model::count_scale() // TODO: STEP DEPENDS ON IT?
{
	const int       single_display = 0;
	const int       pixelart_display_width = 480;
	SDL_DisplayMode Current_display;

	SDL_GetCurrentDisplayMode(single_display, &Current_display);

	return (Current_display.w / pixelart_display_width);
}
