#include "sprite.hpp"

Sprite::Sprite(Graphics& Graphics, const std::string passed_name,
               const Uint32 passed_single_frame_time_ms):
               name(passed_name),
               single_frame_time_ms(passed_single_frame_time_ms)
{
	is_initialized    = false;
	current_frame_idx = 0;

	// if(!load_textures(Graphics))
	// {
	// 	return;
	// }

	if(single_frame_time_ms == 0) // No animation.
	{
		Textures[current_frame_idx] = Graphics.load_texture(name);
		if(Textures[current_frame_idx] == nullptr)
		{
			return;
		}
	}
	else
	{
		if(!load_animation(Graphics))
		{
			return;
		}
	}

	/* As there is only the first texture size check, trying to load animation
	with various texture sizes may brake it's rendering. */
	if(SDL_QueryTexture(Textures[current_frame_idx], nullptr, nullptr,
	   &Geometry.w, &Geometry.h) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the size of the texture: " + name);
		return;
	}
	pos_x = 0.0;
	pos_y = 0.0;

	Geometry.w *= Graphics.pixelart_px_sz;
	Geometry.h *= Graphics.pixelart_px_sz;

	is_initialized = true;
}

Sprite::~Sprite()
{
	if(single_frame_time_ms == 0)
	{
		SDL_DestroyTexture(Textures[single_frame_time_ms]);
	}
	else
	{
		for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
		{
			SDL_DestroyTexture(Textures[idx]);
		}
	}
}

void Sprite::move(Graphics& Graphics, const double offset_x,
                  const double offset_y)
{
	pos_x += offset_x * Graphics.delta_time_s * Graphics.pixelart_px_sz;
	pos_y += offset_y * Graphics.delta_time_s * Graphics.pixelart_px_sz;
}

bool Sprite::load_textures(Graphics& Graphics)
{
	SDL_Surface* Image;

	if(single_frame_time_ms == 0) // No animation.
	{
		Image = Graphics.load_image(name);
		if(Image == nullptr)
		{
			return false;
		}

		Textures[current_frame_idx] = SDL_CreateTextureFromSurface(Graphics.Renderer, Image);
		if(Textures[current_frame_idx] == nullptr)
		{
			error::show_box("Can't create the texture from the image: " + name);
			return false;
		}
		SDL_FreeSurface(Image);
	}
	else // Dir with animations.
	{
		for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
		{
			Image = Graphics.load_image(name + SEPARATOR + std::to_string(idx));
			if(Image == nullptr)
			{
				return false;
			}
			Textures[idx] = SDL_CreateTextureFromSurface(Graphics.Renderer, Image);
			if(Textures[idx] == nullptr)
			{
				return false;
			}
			SDL_FreeSurface(Image);
		}
	}
	return false;
}

bool Sprite::load_animation(Graphics& Graphics)
{
	for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
	{
		Textures[idx] = Graphics.load_texture(name + SEPARATOR
		                                      + std::to_string(idx));
		if(Textures[idx] == nullptr)
		{
			return false;
		}
	}
	return true;
}

void Sprite::animate(const Graphics& Graphics)
{
	if(single_frame_time_ms > 0)
	{
		frame_elapsed_time_ms += Graphics.delta_time_s * 1000.0;

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

bool Sprite::render(Graphics& Graphics)
{
	animate(Graphics);

	Geometry.x = pos_x;
	Geometry.y = pos_y;

	if(SDL_RenderCopy(Graphics.Renderer, Textures[current_frame_idx], nullptr,
	   &Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't render the: " + name);
		return false;
	}
	return true;
}
