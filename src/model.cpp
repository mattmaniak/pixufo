#include "model.hpp"
#include "error.hpp"
#include "rendering.hpp"
#include "keyboard.hpp"

Model::Model(Rendering* Rendering, const std::string passed_name,
             const float passed_max_speed): name(passed_name),
             max_speed(passed_max_speed)
{
	Texture = Rendering->load_texture(name);
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

	Geometry.w *= Rendering->pixelart_pixel_sz();
	Geometry.h *= Rendering->pixelart_pixel_sz();
	Geometry.x  = pos_x = 0.0f;
	Geometry.y  = pos_y = 0.0f;

	min_x = max_x = min_y = max_y = 0; // Reanitialized in derived models.

	step = 0.0f;

	initialized = true;
}

Model::~Model()
{
	SDL_DestroyTexture(Texture);
}
