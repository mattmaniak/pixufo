#include "background.hpp"

Background::Background(Graphics* Graphics, const std::string name):
Model(Graphics, name, 0.0f)
{
	min_x = -Geometry.w;
	min_y = -Geometry.h;
	max_x = max_y = 0;
}
