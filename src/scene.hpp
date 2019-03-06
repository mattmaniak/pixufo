#ifndef SCENE_HPP
#define SCENE_HPP

#include "background.hpp"
#include "graphics.hpp"

class Scene
{
public:
	bool is_initialized;

	int width;
	int height;

	Background* Bg;

	Scene(Graphics&, const std::string);
	~Scene();
};

#endif
