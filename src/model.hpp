#ifndef MODELS_HPP
#define MODELS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#define PIXELART_DISPLAY_WIDTH 640.0f

class Graphics;

namespace model
{
	class Basic
	{
		protected:
		SDL_Texture* Texture_;  // Driver-specific representation of data.

		public:
		bool         initialized;
		SDL_Rect     Geometry; // Texture_'s position and size.
		float        pos_x;
		float        pos_y;
		float        step;     // Pixel position move in a one frame.
		float        speed;    // Pixel position move in a one second.

		Basic(Graphics* Graphics, const std::string name, const float spd);
		~Basic();

		bool  render(Graphics* Graphics);
		float count_scale();
	};

	class Enemy: public Basic // TODO: INHERIT FROM PLANET?
	{
		public:
		bool     visible;
		float    distance_to_player;

		// float speed;
		// float step;

		Enemy(Graphics* Graphics, const std::string name, const float spd);
		bool render(Graphics* Graphics);
	};

	class Player: public Basic
	{
		public:
		// float    speed;
		// float    step;

		Player(Graphics* Graphics, const std::string name, const float spd);
		bool render(Graphics* Graphics);
	};

	class Background: public Basic
	{
		public:

		Background(Graphics* Graphics, const std::string name);

		bool tile(Graphics* Graphics);
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
