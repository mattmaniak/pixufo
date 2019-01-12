#include "game.hpp"
#include "graphics.hpp"
#include "sdlwrap.hpp"
#include "model.hpp"

Model::Model(Graphics* Graphics, const std::string name, const float _speed)
: _name(name), speed(_speed)
{
	SDL_Surface* Image = sdlwrap::load_image(_name);

	Geometry.x = x = 0.0f;
	Geometry.y = y = 0.0f;
	Geometry.w = Image->w * count_scale();
	Geometry.h = Image->h * count_scale();

	_texture = Graphics->create_texture(Image); // TODO: CHECK.
	SDL_FreeSurface(Image);
}

int Model::render(Graphics* Graphics)
{
	Geometry.x = x;
	Geometry.y = y;

	step = speed * count_scale() * Graphics->delta_time;

	if(SDL_RenderCopy(Graphics->Renderer, _texture, NULL, &Geometry) != SUCCESS)
	{
		std::cerr << SDL_GetError() << std::endl;
		return -1;
	}
	return 0;
}

int Model::count_scale() // TODO: STEP DEPENDS ON IT?
{
	const int       pixelart_screen_width = 360;
	SDL_DisplayMode Current_screen_settings;

	SDL_GetCurrentDisplayMode(0, &Current_screen_settings);

	return (Current_screen_settings.w / pixelart_screen_width);
}
