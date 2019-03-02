#include "scene.hpp"

Scene::Scene(Graphics& Graphics, const std::string bg_name)
{
	Bg = new Background(Graphics, bg_name);
	if(!Bg->is_initialized)
	{
		is_initialized = false;
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
