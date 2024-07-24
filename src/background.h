// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_BACKGROUND_H_
#define SRC_BACKGROUND_H_

#include <limits>
#include <string>

#include "./sprite.h"

class Background: public Sprite {
 public:
  Background(Graphics&, std::string);

  bool tile_and_render(Graphics&);  // Of course infinite.

 private:
  void _scroll_endlessly();
};

#endif  // SRC_BACKGROUND_H_
