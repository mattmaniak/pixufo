#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Model
{
	std::string  _path;
	SDL_Texture* _texture; // Driver-specific representation of data.

	void _error(const std::string message);

	public:
	SDL_Rect dimensions; // Texture's position and size.
	int      speed;      // Pixels offset that can step in a single frame.
	float    x;
	float    y;

	Model(Game* PixUfo, const std::string _path, const int _speed);

	void render(SDL_Renderer* renderer, int _x, int _y);
	void destroy();
};

#endif
