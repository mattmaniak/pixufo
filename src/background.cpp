#include "background.hpp"

Background::Background(Graphics* Graphics, const std::string name):
Model(Graphics, name, 0.0f, 0)
{
	min_x = -Geometry.w;
	min_y = -Geometry.h;
	max_x = max_y = 0;
}

void Background::inf_scroll()
{
	if(pos_x > max_x) // Background shifted right.
	{
		pos_x -= Geometry.w; // Move the background one tile left.
	}
	else if(pos_x < min_x) // Background shifted left.
	{
		pos_x += Geometry.w; // Move the background one tile right.
	}
	if(pos_y > max_y) // Background shifted down.
	{
		pos_y -= Geometry.h; // Move the background one tile up.
	}
	else if(pos_y < min_y) // Background shifted up.
	{
		pos_y += Geometry.h; // Move the background one tile down.
	}
}

void Background::move(Graphics* Graphics, const float offset_x,
                      const float offset_y)
{
	pos_x += offset_x * Graphics->delta_time_s * Graphics->pixelart_px_sz();
	pos_y += offset_y * Graphics->delta_time_s * Graphics->pixelart_px_sz();
}
