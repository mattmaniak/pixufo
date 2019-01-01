#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

#define MIN_RESOLUTION_W 1280
#define MIN_RESOLUTION_H 720

// How many times screen's width is bigger than the pixelarts' pixel.
#define SCREEN_TO_PIXEL_RATIO 480

// TODO.
#define FPS         60
#define FRAME_DELAY (1000 / FPS)

class Game
{
	void _error(const std::string message);

	public:
	bool            runtime;
	SDL_DisplayMode screen;
	SDL_Event       event;
	SDL_Window*     window;
	SDL_Renderer*   renderer;

	Game();

	SDL_Surface* load_image(const std::string path);
	SDL_Texture* create_texture(SDL_Surface* image);
	void         loop();
	void         quit();

	~Game();

	class Player
	{
		bool _error(const std::string message);

		public:
		std::string  path;
		SDL_Surface* image;      // Just a bitmap and some metadata.
		SDL_Texture* texture;    // Driver-specific representation of data.
		SDL_Rect     dimensions; // Texture's position and size.
		int          speed;      // Pixels offset that can step in a single frame.
		float        x;
		float        y;

		Player(const std::string _path, const int _speed);

		void render(int _x, int _y);
		bool destroy();

		~Player();
	};
};

#endif
