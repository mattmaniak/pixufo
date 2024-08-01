// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include <array>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

#include "error.h"
#include "graphics.h"
#include "os_env.h"

#define FRAMES_NUMBER 6

class Sprite {
 public:
  const std::string name;

  std::array<SDL_Texture*, FRAMES_NUMBER> textures;
  std::size_t                             current_frame_idx;

  SDL_Rect transform;  // Textures's position and size.
  double   pos_x;      // Theoretical (virtual) positions.
  double   pos_y;

  Sprite(Graphics&, std::string, Uint32);
  virtual ~Sprite();

  void         move(Graphics&, double, double);
  void         animate(Graphics&);
  virtual bool render(Graphics&);

 private:
  const Uint32 current_frame_start_time_ms_;
  Uint32       current_frame_elapsed_time_ms_;

  bool load_textures_(Graphics&);
};

#endif  // SRC_SPRITE_H_
