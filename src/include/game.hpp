#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#define SUCCESS 0

#define UNUSED_SIZE 0

#define MIN_RESOLUTION_W 1280
#define MIN_RESOLUTION_H 720

// TODO.
#define FPS         60.0
#define FRAME_DELAY (1.0 / FPS)

class Game
{
	void _error(const std::string message);

	public:
	SDL_Event       event;
	SDL_DisplayMode display;
	SDL_Window*     window;
	SDL_Renderer*   renderer;
	double          delta_time; // Single frame's time in seconds.

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
		SDL_Texture* texture;  // Driver-specific representation of data.
		SDL_Rect     geometry; // Texture's position and size.
		int          speed;    // Pixels offset that can step in a single frame.
		double       x;
		double       y;

		Player(const std::string _path, const int _speed);

		void render(int _x, int _y);
		void destroy();

		~Player();
	};
};

#endif
