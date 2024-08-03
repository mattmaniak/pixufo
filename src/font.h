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
  double             pos_x_;
  double             pos_y_;
  SDL_Rect           transform_;  // Textures's position and size.

  Font(Graphics&, std::string, unsigned int);
  ~Font();

  bool Render(Graphics&);

 private:
  const std::string  name_;
  TTF_Font*          font_;
  const std::string  text_;
  SDL_Color          color_;
  SDL_Texture*       texture_;
};

#endif  // SRC_FONT_H_
