#ifndef FONT_HPP
#define FONT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "error.hpp"
#include "os_env.hpp"
#include "graphics.hpp"

#define FONTNAME "Blox2.ttf"

class Font
{
public:
	const unsigned int size;
	double             pos_x;
	double             pos_y;
	SDL_Rect           Geometry; // Textures's position and size.

	Font(Graphics&, const std::string, const unsigned int);
	~Font();

	bool render(Graphics&);

private:
	const std::string  name_;
	TTF_Font*          Font_;
	const std::string  text_;
	SDL_Color          Color_;
	SDL_Texture*       Texture_;
};

#endif
