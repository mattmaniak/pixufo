#include "model.hpp"

Model::Model(Graphics* Graphics, const std::string passed_name,
             const float passed_speed): name(passed_name), speed(passed_speed)
{
	Texture = Graphics->load_texture(name);
	if(Texture == nullptr)
	{
		initialized = false;
		return;
	}

	if(SDL_QueryTexture(Texture, nullptr, nullptr, &Geometry.w, &Geometry.h)
	   != SDL2_SUCCESS)
	{
		error::show_box("Can't get a texture size: " + name + '.');
		initialized = false;
		return;
	}

	Geometry.w *= Graphics->pixelart_px_sz();
	Geometry.h *= Graphics->pixelart_px_sz();
	Geometry.x  = Geometry.y = pos_x = pos_y = 0.0f;

	min_x = max_x = min_y = max_y = 0; // Reanitialized in derived models.

	step = 0.0f;

	initialized = true;
}

Model::~Model()
{
	SDL_DestroyTexture(Texture);
}

void Model::convert_pos()
{
	// Converts virtual ones to the rendered position.
	Geometry.x = pos_x;
	Geometry.y = pos_y;
}
