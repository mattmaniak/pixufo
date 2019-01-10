#include "include/game.hpp"
#include "include/window.hpp"
#include "include/sdlwrap.hpp"
#include "include/model.hpp"

Model::Model(Window* Window, const std::string path, const float _speed)
: _path(path), speed(_speed)
{
	SDL_Surface* image = sdlwrap::load_image(_path);

	geometry.x = x = 0.0f;
	geometry.y = y = 0.0f;
	geometry.w = image->w * count_scale(Window);
	geometry.h = image->h * count_scale(Window);

	_texture = Window->create_texture(image);
	SDL_FreeSurface(image);
}

void Model::render(Window* Window)
{
	geometry.x = x;
	geometry.y = y;

	step = speed * Window->delta_time;

	if(SDL_RenderCopy(Window->renderer, _texture, NULL, &geometry) != SUCCESS)
	{
		_error("Can't render the texture: " + _path);
	}
}

int Model::count_scale(Window* Window) // TODO: STEP DEPENDS ON IT?
{
	const int pixelart_dot_size = 6; // Eg. 5 px, so pixelarts' dot = 5x5.

	int dot_to_screen_ratio = Window->display.w / pixelart_dot_size;
	int scale_ratio         = Window->display.w / dot_to_screen_ratio;

	return scale_ratio;
}

void Model::_error(const std::string message)
{
	std::cerr << message << std::endl;
	exit(1);
}
