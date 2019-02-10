#include "model.hpp"
#include "background.hpp"

Background::Background(Rendering* Rendering, const std::string name):
Model(Rendering, name, 0.0f)
{
	min_x = -Geometry.w;
	min_y = -Geometry.h;
	max_x = max_y = 0;
}
