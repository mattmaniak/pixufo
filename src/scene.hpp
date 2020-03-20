#ifndef SCENE_HPP
#define SCENE_HPP

#include "background.hpp"
#include "graphics.hpp"

class Scene
{
public:
    Background*  Bg;

    Scene(Graphics&, const std::string);
    ~Scene();

protected:
    unsigned int _width;
    unsigned int _height;
};

#endif
