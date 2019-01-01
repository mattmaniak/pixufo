#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Model
{
	void _error(const std::string message);

	public:
	std::string  path;
	SDL_Surface* image;      // Just a bitmap and some metadata.
	SDL_Texture* texture;    // Driver-specific representation of data.
	SDL_Rect     dimensions; // Texture's position and size.
	int          speed;      // Pixels offset that can step in a single frame.
	float        x;
	float        y;

	Model(Game* PixUfo, const std::string _path, const int _speed);

	void render(Game* PixUfo, int _x, int _y);
	void destroy();

	~Model();
};

#endif
