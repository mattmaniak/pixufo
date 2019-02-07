#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#define PIXELART_DISPLAY_WIDTH 720.0f

class Graphics;
class Keyboard;

class Model
{
	public:
	const std::string path;
	bool              initialized;

	SDL_Texture*      Texture;  // Driver-specific representation of data.
	SDL_Rect          Geometry; // Texture's position and size.

	float             pos_x;    // Virtual Y-position to use with a delta.
	float             pos_y;    // Virtual X-position to use with a delta.
	float             step;     // Pixel position move in a one frame.
	float             speed;    // Pixel position move in a one second.

	int               min_x;
	int               max_x;
	int               min_y;
	int               max_y;

	Model(Graphics* Graphics, const std::string name, const float passed_speed);
	~Model();

	// To fit a screen width and render with the same size everywhere.
	float pixelart_pixel_sz(); // TODO: IN GRAPHICS.
};

class Button: public Model
{
	public:
	const unsigned int idx;

	Button(Graphics* Graphics, const std::string name, const int idx);
	bool render(Graphics* Graphics, unsigned int current_idx);
};

#endif
