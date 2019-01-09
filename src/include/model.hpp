#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

class Model
{
	std::string  _path;
	SDL_Texture* _texture; // Driver-specific representation of data.

	void _error(const std::string message);

	public:
	SDL_Rect geometry; // Texture's position and size.
	float    speed;    // Pixels offset that can move in a one second.
	float    step;     // Real pixels per frame move.
	float    x;
	float    y;
	float    distance_to_player;

	Model(Window* Window, const std::string _path, const float _speed);

	void render(Window* Window);
	int  count_scale(Window* Window);
	void destroy();
};

#endif
