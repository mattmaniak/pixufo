#include "sprite.hpp"

Sprite::Sprite(Graphics& Graphics, const std::string passed_name,
               const double passed_speed,
               const Uint32 passed_single_frame_time_ms):
               name(passed_name), max_speed(passed_speed),
               single_frame_time_ms(passed_single_frame_time_ms)
{
	const std::string separator = SEPARATOR;

	path = "textures" + separator + name;

	current_frame_idx = 0;

	if(single_frame_time_ms == 0) // No animation.
	{
		Textures[current_frame_idx] = Graphics.load_texture(name);
		if(Textures[current_frame_idx] == nullptr)
		{
			is_initialized = false;
			return;
		}
	}
	else
	{
		if(!load_animation(Graphics))
		{
			is_initialized = false;
			return;
		}
	}

	/* As there is only the first texture size check, trying to load animation
	with various texture sizes may brake it's rendering. */
	if(SDL_QueryTexture(Textures[current_frame_idx], nullptr, nullptr,
	   &Geometry.w, &Geometry.h) != SDL2_SUCCESS)
	{
		error::show_box("Can't get the size of the texture: " + name);
		is_initialized = false;
		return;
	}
	Geometry.w *= Graphics.pixelart_px_sz;
	Geometry.h *= Graphics.pixelart_px_sz;
	step        = 0.0;

	if(!load_hitbox())
	{
		is_initialized = false;
		return;
	}
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
		// TODO: EXECUTES 2 TIMES WITH NEBULA_WASP.
		std::cout << name << std::endl;
		for(std::size_t idx = 0; idx < FRAMES_AMOUNT; idx++)
		{
			SDL_DestroyTexture(Textures[idx]);
		}
	}
}

bool Sprite::load_hitbox()
{
	std::size_t rects_amount = 0;

	std::string path_to_file = path + SEPARATOR + "hitbox";

	FILE* Hitbox_parts_file = std::fopen(path_to_file.c_str(), "r");

	if(Hitbox_parts_file == nullptr)
	{
		// error::show_box("Can't load the hitbox file for: " + name);
		// return false;
		Hitbox_parts.push_back({0, 0, Geometry.w, Geometry.h});
		return true;
	}
	for(;;)
	{
		Hitbox_parts.push_back({0, 0, 0, 0});

		std::fscanf(Hitbox_parts_file, "(%d, %d) [%d, %d]\n",
		            &Hitbox_parts[rects_amount].x,
		            &Hitbox_parts[rects_amount].y,
		            &Hitbox_parts[rects_amount].w,
		            &Hitbox_parts[rects_amount].h);

		if(std::feof(Hitbox_parts_file))
		{
			break;
		}
		rects_amount++;
		if(rects_amount > static_cast<std::size_t>(Geometry.w * Geometry.h))
		{
			error::show_box("Wrong hitbox for: " + name);
			return false;
		}
	}
	std::fclose(Hitbox_parts_file);

	return true;
}

void Sprite::calc_pos(Graphics& Graphics)
{
	Geometry.x = pos_x; // Converts virtual position to the rendered position.
	Geometry.y = pos_y;

	step = max_speed * Graphics.delta_time_s * Graphics.pixelart_px_sz;
}

void Sprite::move(Graphics& Graphics, const double offset_x, const double offset_y)
{
	pos_x += offset_x * Graphics.delta_time_s * Graphics.pixelart_px_sz;
	pos_y += offset_y * Graphics.delta_time_s * Graphics.pixelart_px_sz;
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
	calc_pos(Graphics);
	animate(Graphics);

	if(SDL_RenderCopy(Graphics.Renderer, Textures[current_frame_idx], nullptr,
	   &Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't render the: " + path);
		return false;
	}

	if(Hitbox_parts.size() > 0)
	{
		SDL_Rect Hbox_part;

		for(std::size_t idx = 0; idx < Hitbox_parts.size(); idx++)
		{
			Hbox_part.w = Hitbox_parts[idx].w * Graphics.pixelart_px_sz;
			Hbox_part.h = Hitbox_parts[idx].h * Graphics.pixelart_px_sz;
			Hbox_part.x = pos_x + (Hitbox_parts[idx].x
			              * Graphics.pixelart_px_sz);

			Hbox_part.y = pos_y + (Hitbox_parts[idx].y
			              * Graphics.pixelart_px_sz);

			if(name == "ufo")
			{
				Hbox_part.w /= Graphics.pixelart_px_sz;
				Hbox_part.h /= Graphics.pixelart_px_sz;
			}
			if(SDL_SetRenderDrawColor(Graphics.Renderer, 0, 255, 0, 100)
			   != SDL2_SUCCESS)
			{
				error::show_box("Can't set color for: " + path + " hitbox.");
				return false;
			}
			if(SDL_RenderFillRect(Graphics.Renderer, &Hbox_part) != SDL2_SUCCESS)
			{
				error::show_box("Can't render the hitbox part for: " + path);
				return false;
			}
		}
	}
	return true;
}
