#include "entity.hpp"

Entity::Entity(Graphics& Graphics, const std::string name,
               const double passed_speed,
               const Uint32 passed_single_frame_time_ms):
Sprite(Graphics, name, passed_single_frame_time_ms), max_speed(passed_speed)
{
	is_initialized = false;

	if(!load_hitbox())
	{
		return;
	}
	step = 0.0;

	is_initialized = true;
}

bool Entity::load_hitbox()
{
	const std::string path_to_file = HITBOXES_PATH + name;
	std::size_t       rects_amount = 0;

	FILE* Hitbox_parts_file = std::fopen(path_to_file.c_str(), "r");

	if(Hitbox_parts_file == nullptr)
	{
		// error::show_box("Can't load the hitbox file for: " + name);
		// return false;

		Hitbox_parts.push_back({0, 0, Geometry.w, Geometry.h});
		has_custom_hitbox = false;
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

		if((Hitbox_parts[rects_amount].x == 0) // Empty file scenario.
		   && (Hitbox_parts[rects_amount].y == 0)
		   && (Hitbox_parts[rects_amount].w == 0)
		   && (Hitbox_parts[rects_amount].h == 0))
		{
			Hitbox_parts[rects_amount] = {0, 0, Geometry.w, Geometry.h};
			std::fclose(Hitbox_parts_file);
			has_custom_hitbox = false;
			return true;
		}

		if(std::feof(Hitbox_parts_file))
		{
			break;
		}
		rects_amount++;

		if(rects_amount > static_cast<std::size_t>(Geometry.w * Geometry.h))
		{
			error::show_box("Wrong hitbox for: " + name);
			std::fclose(Hitbox_parts_file);
			return false;
		}
	}
	std::fclose(Hitbox_parts_file);
	has_custom_hitbox = true;

	return true;
}

void Entity::randomize_initial_pos()
{
	std::mt19937 prng;
	prng.seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type>
	distributor_x(min_x, max_x);

	std::uniform_int_distribution<std::mt19937::result_type>
	distributor_y(min_y, max_y);

	pos_x = distributor_x(prng);
	pos_y = distributor_y(prng);
}

bool Entity::render(Graphics& Graphics)
{
	SDL_Rect Hbox_part;

	Geometry.x = pos_x; // Converts virtual position to the rendered position.
	Geometry.y = pos_y;

	step = max_speed * Graphics.delta_time_s * Graphics.pixelart_px_sz;

	animate(Graphics);

	if(SDL_RenderCopy(Graphics.Renderer, Textures[current_frame_idx], nullptr,
	   &Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't render the: " + name);
		return false;
	}
	for(std::size_t idx = 0; idx < Hitbox_parts.size(); idx++)
	{
		Hbox_part.w = Hitbox_parts[idx].w * Graphics.pixelart_px_sz;
		Hbox_part.h = Hitbox_parts[idx].h * Graphics.pixelart_px_sz;
		Hbox_part.x = pos_x + (Hitbox_parts[idx].x * Graphics.pixelart_px_sz);
		Hbox_part.y = pos_y + (Hitbox_parts[idx].y * Graphics.pixelart_px_sz);

		if(!has_custom_hitbox)
		{
			Hbox_part.w /= Graphics.pixelart_px_sz;
			Hbox_part.h /= Graphics.pixelart_px_sz;
		}
		if(SDL_SetRenderDrawColor(Graphics.Renderer, 0, 255, 0, 100)
		   != SDL2_SUCCESS)
		{
			error::show_box("Can't set color for: " + name + " hitbox.");
			return false;
		}
		if(SDL_RenderFillRect(Graphics.Renderer, &Hbox_part) != SDL2_SUCCESS)
		{
			error::show_box("Can't render the hitbox part for: " + name);
			return false;
		}
	}
	return true;
}
