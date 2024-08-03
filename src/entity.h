// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <random>
#include <string>
#include <vector>

#include "sprite.h"

class Entity: public Sprite {  // Just sprite but more physical - with hitbox.
 public:
  int min_x_;
  int max_x_;
  int min_y_;
  int max_y_;

  Uint32 hidden_timeout_ms_;

  double                max_speed_;  // Pixel position Move in a one second.
  double                step_;       // Pixel position Move in a one frame.
  std::vector<SDL_Rect> hitbox_parts_;

  Entity(Graphics&, std::string, double, Uint32);

  bool LoadHitbox(Graphics&);
  void RandomizeInitialPos();
  bool Render(Graphics&);
};

#endif  // SRC_ENTITY_H_
