#include "scene.hpp"

Scene::Scene(Graphics& Graphics, const std::string bg_name)
{
	is_initialized = false;

	Bg = new Background(Graphics, bg_name);
	if(!Bg->is_initialized)
	{
		return;
	}
	is_initialized = true;
}

Scene::~Scene()
{
	if(Bg->is_initialized)
	{
		delete Bg;
	}
}
