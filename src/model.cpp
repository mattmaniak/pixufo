#include "game.hpp"
#include "model.hpp"

Model::Model(Game* PixUfo, const std::string _path, const int _speed)
: path(_path), speed(_speed)
{
	dimensions.x = x = 0.0;
	dimensions.y = y = 0.0;

	image = PixUfo->load_image(path);

	dimensions.w = image->w * (PixUfo->screen.w / SCREEN_TO_PIXEL_RATIO);
	dimensions.h = image->h * (PixUfo->screen.w / SCREEN_TO_PIXEL_RATIO);

	texture = SDL_CreateTextureFromSurface(PixUfo->renderer, image);
	if(texture == nullptr)
	{
		_error("Can't create the texture from: " + path);
		exit(1);
	}
}

void Model::render(Game* PixUfo, int _x, int _y)
{
	dimensions.x = _x;
	dimensions.y = _y;

	if(SDL_RenderCopy(PixUfo->renderer, texture, NULL, &dimensions) != SUCCESS)
	{
		_error("Can't render the texture: " + path);
	}
}

bool Model::destroy()
{
	std::cout << "Model destructor." << std::endl;
	if(image != nullptr)
	{
		SDL_FreeSurface(image);
	}
	if(texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	return 0;
}

bool Model::_error(const std::string message)
{
	std::cerr << message << std::endl;
	destroy();
	return 1;
}

Model::~Model()
{
	destroy();
}
