#include "model.hpp"

Model::Model(Graphics* Graphics, const std::string passed_name,
             const float passed_speed,
             const Uint32 passed_single_frame_time_ms):
             name(passed_name), speed(passed_speed),
             single_frame_time_ms(passed_single_frame_time_ms)
{
	current_frame_idx = 0;

	if(single_frame_time_ms == 0) // No animation.
	{
		Textures[current_frame_idx] = Graphics->load_texture(name);
		if(Textures[current_frame_idx] == nullptr)
		{
			initialized = false;
			return;
		}
	}
	else
	{
		if(!load_animation(Graphics))
		{
			initialized = false;
			return;
		}
	}

	/* As there is only the first texture size check, trying to load animation
	with various texture sizes may brake it's rendering. */
	if(SDL_QueryTexture(Textures[current_frame_idx], nullptr, nullptr,
	   &Geometry.w, &Geometry.h) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the size of the texture: " + name);
		initialized = false;
		return;
	}
	Geometry.w *= Graphics->pixelart_px_sz();
	Geometry.h *= Graphics->pixelart_px_sz();
	step        = 0.0f;

	initialized = true;
}

Model::~Model()
{
	if(single_frame_time_ms == 0)
	{
		SDL_DestroyTexture(Textures[0]);
	}
	else
	{
		for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
		{
			SDL_DestroyTexture(Textures[idx]);
		}
	}
	Textures.empty();
}

void Model::calc_pos(Graphics* Graphics)
{
	// Converts virtual ones to the rendered position.
	Geometry.x = pos_x;
	Geometry.y = pos_y;

	step = speed * Graphics->delta_time_s * Graphics->pixelart_px_sz();
}

bool Model::load_animation(Graphics* Graphics)
{
#ifdef _WIN32
	const std::string separator = "\\";

#else
#ifdef __linux__
	const std::string separator = "/";
#endif

#endif

	for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
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
	if(single_frame_time_ms > 0)
	{
		frame_elapsed_time_ms += Graphics->delta_time_s * 1000.0f;

		if(frame_elapsed_time_ms >= single_frame_time_ms)
		{
			frame_elapsed_time_ms = 0;
			current_frame_idx++;
		}
		if(current_frame_idx >= FRAMES_AMOUNT)
		{
			current_frame_idx = 0;
		}
	}
}
