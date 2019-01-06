#include "game.hpp"
#include "model.hpp"

Model::Model(Game* PixUfo, const std::string path, const float _step)
: _path(path), step(_step)
{
	SDL_Surface* image = PixUfo->load_image(_path);

	geometry.x = x = 0.0f;
	geometry.y = y = 0.0f;
	geometry.w = image->w * (PixUfo->display.w / SCREEN_TO_PIXEL_RATIO);
	geometry.h = image->h * (PixUfo->display.w / SCREEN_TO_PIXEL_RATIO);

	PixUfo->delta_time = 1.0f / PixUfo->display.refresh_rate;

	_texture = PixUfo->create_texture(image);
	SDL_FreeSurface(image);
}

void Model::render(Game* PixUfo)
{
	geometry.x = x;
	geometry.y = y;

	speed = step * PixUfo->delta_time;

	if(SDL_RenderCopy(PixUfo->renderer, _texture, NULL, &geometry) != SUCCESS)
	{
		_error("Can't render the texture: " + _path);
	}
}

void Model::_error(const std::string message)
{
	std::cerr << message << std::endl;
	exit(1);
}
