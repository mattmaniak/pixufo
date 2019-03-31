#ifndef SCENE_HPP
#define SCENE_HPP

#include "background.hpp"
#include "graphics.hpp"

class Scene
{
public:
    unsigned int width;
    unsigned int height;
    Background*  Bg;

    Scene(Graphics&, const std::string);
    ~Scene();
};

#endif
