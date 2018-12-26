#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#define SUCCESS 0

#define GAME_RESOLUTION_W 1280
#define GAME_RESOLUTION_H 720

class Game
{
	public:
	bool          runtime;
	int           w;
	int           h;
	SDL_Event     event;
	SDL_Window*   window;
	SDL_Renderer* renderer;
	SDL_Texture*  background;

	Game();

	SDL_Surface* load_image(const std::string path);
	SDL_Texture* load_texture(const std::string path);
	bool         quit();
	bool         error(const std::string message);

	~Game();
};

#endif
