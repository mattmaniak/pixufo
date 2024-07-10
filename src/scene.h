#ifndef SCENE_H_
#define SCENE_H_

#include <string>

#include "./background.h"
#include "./graphics.h"

class Scene {
 public:
  Background*  Bg;

  Scene(Graphics&, std::string);
  ~Scene();

 protected:
  unsigned int _width;
  unsigned int _height;
};

#endif  // SCENE_H_
