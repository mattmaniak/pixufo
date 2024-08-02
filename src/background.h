// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_BACKGROUND_H_
#define SRC_BACKGROUND_H_

#include <limits>
#include <string>

#include "sprite.h"

class Background: public Sprite {
 public:
  Background(Graphics&, std::string);

  bool TileAndRender(Graphics&);  // Of course infinite.

 private:
  void ScrollEndlessly();
};

#endif  // SRC_BACKGROUND_H_
