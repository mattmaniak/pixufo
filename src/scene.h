// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_SCENE_H_
#define SRC_SCENE_H_

#include <string>

#include "./background.h"
#include "./graphics.h"

class Scene {
 public:
  Background*  Bg;

  Scene(Graphics&, std::string);
  ~Scene();

 protected:
  Graphics* _Graphics;

  unsigned int _width;
  unsigned int _height;
};

#endif  // SRC_SCENE_H_
