// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_SCENE_H_
#define SRC_SCENE_H_

#include <string>

#include "background.h"
#include "graphics.h"

class Scene {
 public:
  Scene(Graphics&, std::string);
  ~Scene();

  Background* bg_;

 protected:
  Graphics*    graphics_;
  unsigned int height_;
  unsigned int width_;
};

#endif  // SRC_SCENE_H_
