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
    SDL_Rect           geometry; // Textures's position and size.

    Font(Graphics&, std::string, unsigned int);
    ~Font();

    bool render(Graphics&);

private:
    const std::string  _name;
    TTF_Font*          _font;
    const std::string  _text;
    SDL_Color          _color;
    SDL_Texture*       _texture;
};

#endif
