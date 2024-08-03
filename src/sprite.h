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
  Sprite(Graphics&, std::string, Uint32);
  virtual ~Sprite();

  void         CenterOnDisplay(unsigned int, unsigned int);
  void         Move(Graphics&, double, double);
  void         Animate(Graphics&);
  virtual bool Render(Graphics&);

  // Textures's position and size.
  SDL_Rect                                transform_;
  const std::string                       name;

  // Theoretical (virtual) positions.
  double                                  pos_x_;
  double                                  pos_y_;
  std::array<SDL_Texture*, FRAMES_NUMBER> textures_;
  std::size_t                             current_frame_idx_;

 private:
  bool LoadTextures(Graphics&);

  const Uint32 current_frame_start_time_ms_;
  Uint32       current_frame_elapsed_time_ms_;
};

#endif  // SRC_SPRITE_H_
