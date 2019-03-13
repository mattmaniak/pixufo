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
	const std::string name;

	TTF_Font*         Font_ttf;
	const std::string text;
	const int         sz;
	SDL_Color         Color;
	SDL_Texture*      Texture;

	SDL_Rect Geometry; // Textures's position and size.
	double   pos_x;
	double   pos_y;

	Font(Graphics&, const std::string, const int);
	~Font();
};

#endif
