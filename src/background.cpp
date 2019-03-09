#include "background.hpp"

Background::Background(Graphics& Graphics, const std::string name):
Sprite(Graphics, name, 0) {}

void Background::inf_scroll_()
{
	if(pos_x > 0.0) // Background shifted right.
	{
		pos_x -= Geometry.w; // Move the background one tile left.
	}
	else if(pos_x < -Geometry.w) // Background shifted left.
	{
		pos_x += Geometry.w; // Move the background one tile right.
	}
	if(pos_y > 0.0) // Background shifted down.
	{
		pos_y -= Geometry.h; // Move the background one tile up.
	}
	else if(pos_y < -Geometry.h) // Background shifted up.
	{
		pos_y += Geometry.h; // Move the background one tile down.
	}
}

bool Background::tile_and_render(Graphics& Graphics)
{
	// + 1 - extra one for scrolling.
	unsigned int tiles_x = (Graphics.Display.w / Geometry.w) + 1;
	unsigned int tiles_y = (Graphics.Display.h / Geometry.h) + 1;

	if((tiles_x >= std::numeric_limits<unsigned int>::max())
	   || (tiles_y >= std::numeric_limits<unsigned int>::max()))
	{
		error::show_box("Too many tiles in the background.");
		return false;
	}
	inf_scroll_();

	for(unsigned int y = 0; y <= tiles_y; y++) // Tiling.
	{
		for(unsigned int x = 0; x <= tiles_x; x++)
		{
			Geometry.x = pos_x + (x * Geometry.w);
			Geometry.y = pos_y + (y * Geometry.h);

			if(SDL_RenderCopy(Graphics.Renderer, Textures[current_frame_idx],
			   nullptr, &Geometry) != SDL2_SUCCESS)
			{
				error::show_box("Can't render the: " + name
				                + " as the tile background.");
				return false;
			}
		}
	}
	return true;
}
