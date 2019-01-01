#include "game.hpp"
#include "model.hpp"

Model::Model(Game* PixUfo, const std::string path, const int _speed)
: _path(path), speed(_speed)
{
	SDL_Surface* image;

	dimensions.x = x = 0.0;
	dimensions.y = y = 0.0;

	image = PixUfo->load_image(_path);

	dimensions.w = image->w * (PixUfo->screen.w / SCREEN_TO_PIXEL_RATIO);
	dimensions.h = image->h * (PixUfo->screen.w / SCREEN_TO_PIXEL_RATIO);

	_texture = PixUfo->create_texture(image);
	SDL_FreeSurface(image);
}

void Model::render(SDL_Renderer* renderer, int _x, int _y)
{
	dimensions.x = _x;
	dimensions.y = _y;

	if(SDL_RenderCopy(renderer, _texture, NULL, &dimensions) != SUCCESS)
	{
		_error("Can't render the _texture: " + _path);
	}
}

void Model::_error(const std::string message)
{
	std::cerr << message << std::endl;
	exit(1);
}
