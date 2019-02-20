#include "background.hpp"

Background::Background(Graphics* Graphics, const std::string name):
Model(Graphics, name, 0.0f, 0)
{
	min_x = -Geometry.w;
	min_y = -Geometry.h;
	max_x = max_y = 0;
}
