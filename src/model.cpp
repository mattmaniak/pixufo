#include "model.hpp"

Model::Model(Graphics* Graphics, const std::string passed_name,
             const float passed_speed, const bool passed_animated):
             name(passed_name), animated(passed_animated), speed(passed_speed)
{
	if(animated)
	{
		if(!load_animation_files(Graphics))
		{
			initialized = false;
			return;
		}
		current_frame_idx = 0;
		animation_period  = 120;
	}
	else
	{
		Textures[0] = Graphics->load_texture(name);
		if(Textures[0] == nullptr)
		{
			initialized = false;
			return;
		}
	}

	if(SDL_QueryTexture(Textures[0], nullptr, nullptr, &Geometry.w, &Geometry.h)
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
	if(animated)
	{
		for(std::size_t idx = 0; idx < MAX_FRAMES_AMOUNT; idx++)
		{
			SDL_DestroyTexture(Textures[idx]);
		}
	}
	else
	{
		SDL_DestroyTexture(Textures[0]);
	}
	Textures.empty();
}

void Model::convert_pos()
{
	// Converts virtual ones to the rendered position.
	Geometry.x = pos_x;
	Geometry.y = pos_y;
}

bool Model::load_animation_files(Graphics* Graphics)
{
#ifdef _WIN32
	const std::string separator = "\\";

#else
#ifdef __linux__
	const std::string separator = "/";
#endif

#endif

	for(std::size_t idx = 0; idx < MAX_FRAMES_AMOUNT; idx++)
	{
		Textures[idx] = Graphics->load_texture(name + separator
		                                       + std::to_string(idx));
		if(Textures[idx] == nullptr)
		{
			return false;
		}
	}
	return true;
}

void Model::animate(Graphics* Graphics)
{
	animation_elapsed_time += Graphics->delta_time * 1000.0f;

	if(animation_elapsed_time > animation_period)
	{
		animation_elapsed_time = 0;
		current_frame_idx++;
	}
	if(current_frame_idx >= MAX_FRAMES_AMOUNT)
	{
		current_frame_idx = 0;
	}
}
