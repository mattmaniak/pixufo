#include "scene.h"

Scene::Scene(Graphics& graphics, std::string bg_name)
{
    try
    {
        Bg = new Background(graphics, bg_name);
    }
    catch (std::runtime_error)
    {
        throw std::runtime_error("");
    }
}

Scene::~Scene()
{
    delete Bg;
}
