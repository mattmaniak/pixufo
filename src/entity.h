// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <random>
#include <string>
#include <vector>

#include "sprite.h"

class Entity: public Sprite {  // Just sprite but more physical - with hitbox.
 public:
  int min_x;
  int max_x;
  int min_y;
  int max_y;

  Uint32 hidden_timeout_ms;

  double                max_speed;  // Pixel position move in a one second.
  double                step;       // Pixel position move in a one frame.
  std::vector<SDL_Rect> hitbox_parts;

  Entity(Graphics&, std::string, double, Uint32);

  bool load_hitbox(Graphics&);
  void randomize_initial_pos();
  bool render(Graphics&);
};

#endif  // SRC_ENTITY_H_
