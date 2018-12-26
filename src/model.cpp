#include "game.hpp"
#include "model.hpp"

Model::Model(Game* Game, const std::string path, const int _x,
const int _y, const int _step) : step(_step)
{
	image = Game->load_image(path);

	dimensions.x = _x;
	dimensions.y = _y;
	dimensions.w = image->w * SCALE_FACTOR;
	dimensions.h = image->h * SCALE_FACTOR;

	texture = SDL_CreateTextureFromSurface(Game->renderer, image);
	if(texture == nullptr)
	{
		_error("Can't create the texture from: " + path);
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
