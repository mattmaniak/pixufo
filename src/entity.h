// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <string>
#include <vector>

#include "sprite.h"
#include "utils.h"

// Just sprite but more physical - with hitbox.
class Entity: public Sprite {
 public:
  Entity(Graphics&, std::string, double, Uint32);

  bool LoadHitbox(Graphics&);
  bool Render(Graphics&);
  void RandomizeInitialPos();

  Uint32                hidden_timeout_ms_;
  double                max_speed_;  // Pixel position Move in a one second.
  double                step_;       // Pixel position Move in a one frame.
  int                   max_x_;
  int                   max_y_;
  int                   min_x_;
  int                   min_y_;
  std::vector<SDL_Rect> hitbox_parts_;
};

#endif  // SRC_ENTITY_H_
