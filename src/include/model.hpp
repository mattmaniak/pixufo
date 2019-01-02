#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

// How many times screen's width is bigger than the pixelarts' pixel.
#define SCREEN_TO_PIXEL_RATIO 360

class Model
{
	std::string  _path;
	SDL_Texture* _texture; // Driver-specific representation of data.

	void _error(const std::string message);

	public:
	SDL_Rect dimensions; // Texture's position and size.
	float    speed;      // Pixels offset that can step in a single frame.
	float    x;
	float    y;

	Model(Game* PixUfo, const std::string _path, const float _speed);

	void render(SDL_Renderer* renderer);
	void destroy();
};

#endif
