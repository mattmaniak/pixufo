#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

// How many times screen's width is bigger than the pixelarts' pixel.
#define SCREEN_TO_PIXEL_RATIO 320

class Model
{
	std::string  _path;
	SDL_Texture* _texture; // Driver-specific representation of data.

	void _error(const std::string message);

	public:
	SDL_Rect dimensions; // Texture's position and size.
	double   step;       // Pixels offset that can step in a one second.
	double   speed;      // Real pixels per frame move.
	double   x;
	double   y;

	Model(Game* PixUfo, const std::string _path, const double _step);

	void render(Game* PixUfo);
	void destroy();
};

#endif
