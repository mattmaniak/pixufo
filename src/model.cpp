#include "game.hpp"
#include "model.hpp"

Model::Model(Game* PixUfo, const std::string path, const double _step)
: _path(path), step(_step)
{
	SDL_Surface* image = PixUfo->load_image(_path);

	dimensions.x = x = 0.0;
	dimensions.y = y = 0.0;
	dimensions.w = image->w * (PixUfo->display.w / SCREEN_TO_PIXEL_RATIO);
	dimensions.h = image->h * (PixUfo->display.w / SCREEN_TO_PIXEL_RATIO);

	_texture = PixUfo->create_texture(image);
	SDL_FreeSurface(image);
}

void Model::render(Game* PixUfo)
{
	dimensions.x = x;
	dimensions.y = y;

	speed = step * PixUfo->delta_time;

	if(SDL_RenderCopy(PixUfo->renderer, _texture, NULL, &dimensions) != SUCCESS)
	{
		_error("Can't render the texture: " + _path);
	}
}

void Model::_error(const std::string message)
{
	std::cerr << message << std::endl;
	exit(1);
}
