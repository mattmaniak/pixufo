// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_SCENE_H_
#define SRC_SCENE_H_

#include <string>

#include "background.h"
#include "graphics.h"

class Scene {
 public:
  Background* bg_;

  Scene(Graphics&, std::string);
  ~Scene();

 protected:
  Graphics* graphics_;

  unsigned int width_;
  unsigned int height_;
};

#endif  // SRC_SCENE_H_
