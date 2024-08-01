// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_FONT_H_
#define SRC_FONT_H_

#include <string>

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif
#include <SDL_ttf.h>

#include "error.h"
#include "graphics.h"
#include "os_env.h"

#define FONT_NAME "Blox2.ttf"

class Font {
 public:
  const unsigned int size;
  double             pos_x;
  double             pos_y;
  SDL_Rect           geometry;  // Textures's position and size.

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

#endif  // SRC_FONT_H_
