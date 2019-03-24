#include "entity.hpp"

Entity::Entity(Graphics& Graphics, const std::string name,
               const double passed_speed,
               const Uint32 passed_single_frame_time_ms):
Sprite(Graphics, name, passed_single_frame_time_ms), max_speed(passed_speed)
{
	if(!load_hitbox(Graphics))
	{
		throw std::runtime_error("");
	}
	step = 0.0;

	hidden_timeout_ms = 0;
}

bool Entity::load_hitbox(Graphics& Graphics)
{
	const std::string path_to_file = HITBOXES_PATH + name;
	std::size_t       rects_amount = 0;

	FILE* Hitbox_parts_file = std::fopen(path_to_file.c_str(), "r");

	if(Hitbox_parts_file == nullptr)
	{
		error::show_box("Can't load the hitbox file for: " + name);
		return false;
	}
	for(;;)
	{
		Hitbox_parts.push_back({0, 0, 0, 0});

		std::fscanf(Hitbox_parts_file, "(%d, %d) [%d, %d]\n",
		            &Hitbox_parts[rects_amount].x,
		            &Hitbox_parts[rects_amount].y,
		            &Hitbox_parts[rects_amount].w,
		            &Hitbox_parts[rects_amount].h);

		Hitbox_parts[rects_amount].w = Hitbox_parts[rects_amount].w
		                               * Graphics.pixelart_px_sz;

		Hitbox_parts[rects_amount].h = Hitbox_parts[rects_amount].h
		                               * Graphics.pixelart_px_sz;

		Hitbox_parts[rects_amount].x = Hitbox_parts[rects_amount].x
		                               * Graphics.pixelart_px_sz;

		Hitbox_parts[rects_amount].y = Hitbox_parts[rects_amount].y
		                               * Graphics.pixelart_px_sz;

		if(((Hitbox_parts[rects_amount].x   == 0) // Empty file scenario.
		   && (Hitbox_parts[rects_amount].y == 0)
		   && (Hitbox_parts[rects_amount].w == 0)
		   && (Hitbox_parts[rects_amount].h == 0))
		   || (Hitbox_parts[rects_amount].x  < 0) // Wrong position or/and size.
		   || (Hitbox_parts[rects_amount].y  < 0)
		   || (Hitbox_parts[rects_amount].w  < 1)
		   || (Hitbox_parts[rects_amount].h  < 1))
		{
			error::show_box("Wrong hitbox for the: " + name);
			return false;
		}
		if(std::feof(Hitbox_parts_file))
		{
			break;
		}
		rects_amount++;

		if(rects_amount > static_cast<std::size_t>(Geometry.w * Geometry.h))
		{
			error::show_box("Too many hitbox parts for: " + name);
			std::fclose(Hitbox_parts_file);

			return false;
		}
	}
	std::fclose(Hitbox_parts_file);

	return true;
}

void Entity::randomize_initial_pos()
{
	std::mt19937 prng;
	prng.seed(std::random_device()());

	std::uniform_int_distribution<> distributor_x(max_x, 2 * max_x);
	std::uniform_int_distribution<> distributor_y(min_y, max_y);

	pos_x = distributor_x(prng);
	pos_y = distributor_y(prng);
}

bool Entity::render(Graphics& Graphics)
{

#ifdef DEBUG
	SDL_Rect Hbox_part;
#endif

	Geometry.x = pos_x;
	Geometry.y = pos_y;

	step = max_speed * Graphics.delta_time_s * Graphics.pixelart_px_sz;

	animate(Graphics);

	if(SDL_RenderCopy(Graphics.Renderer, Textures[current_frame_idx], nullptr,
	   &Geometry) != SDL2_SUCCESS)
	{
		error::show_box("Can't render the: " + name);
		return false;
	}

#ifdef DEBUG
	for(std::size_t idx = 0; idx < Hitbox_parts.size(); idx++)
	{
		Hbox_part.w = Hitbox_parts[idx].w;
		Hbox_part.h = Hitbox_parts[idx].h;
		Hbox_part.x = pos_x + Hitbox_parts[idx].x;
		Hbox_part.y = pos_y + Hitbox_parts[idx].y;

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
#endif

	return true;
}
