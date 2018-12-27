#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Model
{
	bool _error(const std::string message);

	public:
	SDL_Surface* image;      // Just a bitmap and some metadata.
	SDL_Texture* texture;    // Driver-specific representation of data.
	SDL_Rect     dimensions; // Texture's position and size.
	int          step;       // Pixels offset that can step in a single frame.

	Model(Game* PixUfo, const std::string path, const int _x,
	const int _y, const int _step);

	bool destroy();

	~Model();
};

#endif
