#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#define SUCCESS 0

#define MIN_RESOLUTION_W 1280
#define MIN_RESOLUTION_H 720

#define SCREEN_TO_PIXEL_RATIO 240 // TODO: COUNT IT.
#define SCALE_FACTOR          (PixUfo->screen.w / SCREEN_TO_PIXEL_RATIO)

class Game
{
	public:
	bool            runtime;
	SDL_DisplayMode screen;
	SDL_Event       event;
	SDL_Window*     window;
	SDL_Renderer*   renderer;

	Game();

	SDL_Surface* load_image(const std::string path);
	SDL_Texture* load_texture(const std::string path);
	bool         quit();
	bool         error(const std::string message);

	~Game();
};

#endif
