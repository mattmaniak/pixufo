#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#define PIXELART_DISPLAY_WIDTH 720.0f

class Graphics;
class Keyboard;

namespace model
{
	class Basic
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

		Basic(Graphics* Graphics, const std::string name, const float spd);
		~Basic();

		// To fit a screen width and render with the same size everywhere.
		float count_scale();
	};

	class Enemy: public Basic // TODO: INHERIT FROM PLANET?
	{
		public:
		bool     visible;
		float    distance_to_player;

		Enemy(Graphics* Graphics, const std::string name, const float spd);
	};

	class Player: public Basic
	{
		public:
		const float max_levitation_time;
		float       current_levitation_time;

		Player(Graphics* Graphics, const std::string name, const float spd);
	};

	class Background: public Basic
	{
		public:
		Background(Graphics* Graphics, const std::string name);
	};

	class Button: public Basic
	{
		public:
		const unsigned int index;

		Button(Graphics* Graphics, const std::string name, const int idx);
		bool render(Graphics* Graphics, unsigned int current_index);
	};
}

#endif
