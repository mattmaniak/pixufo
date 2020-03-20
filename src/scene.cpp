#include "scene.hpp"

Scene::Scene(Graphics& graphics, const std::string bg_name)
{
    try
    {
        Bg = new Background(graphics, bg_name);
    }
    catch(...)
    {
        throw std::runtime_error("");
    }
}

Scene::~Scene()
{
    delete Bg;
}
