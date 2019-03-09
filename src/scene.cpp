#include "scene.hpp"

Scene::Scene(Graphics& Graphics, const std::string bg_name)
{
	try
	{
		Bg = new Background(Graphics, bg_name);
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
