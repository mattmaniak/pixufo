#include "level.hpp"

Level::Level(Graphics& Graphics, const std::string bg_name,
             const unsigned int passed_enemies_amount):
Scene(Graphics, bg_name), enemies_amount(passed_enemies_amount)
{
	is_initialized = false;

	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	Ufo = new Player(Graphics);
	if(!Ufo->is_initialized)
	{
		return;
	}
	set_model_borders(*Ufo);

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(std::size_t idx = 0; idx < enemies_amount; idx++) // Create all enemies.
	{
		Enemies.push_back(new Entity(Graphics, "nebula_big", 30.0, 180));
		// Enemies.push_back(new Entity(Graphics, "nebula_medium", 60.0, 100));

		if(!Enemies[idx]->is_initialized)
		{
			return;
		}
		set_model_borders(*Enemies[idx]);
		Enemies[idx]->randomize_initial_pos();
	}
	is_initialized = true;
}

Level::~Level()
{
	if(Ufo->is_initialized)
	{
		delete Ufo;
	}
	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		if(Enemies[idx]->is_initialized)
		{
			delete Enemies[idx];
		}
	}
}

void Level::reset()
{
	Ufo->Movements["horizontal"]->keypress_time_s = 0.0;
	Ufo->Movements["vertical"]->keypress_time_s   = 0.0;

	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		Enemies[idx]->randomize_initial_pos();
	}
}

void Level::set_entities_borders(Graphics& Graphics)
{
	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	set_model_borders(*Ufo);

	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		set_model_borders(*Enemies[idx]);
	}
}

bool Level::check_player_collision(Graphics& Graphics)
{
	SDL_Rect Player_hbox_part;
	SDL_Rect Enemy_hbox_part;

	for(std::size_t en_idx = 0; en_idx < Enemies.size(); en_idx++)
	{
		if(SDL_HasIntersection(&Ufo->Geometry,
		                       &Enemies[en_idx]->Geometry))
		{
			for(std::size_t pl_hb_idx = 0; pl_hb_idx < Ufo->Hitbox_parts.size(); pl_hb_idx++)
			{
				Player_hbox_part.w = Ufo->Hitbox_parts[pl_hb_idx].w * Graphics.pixelart_px_sz;
				Player_hbox_part.h = Ufo->Hitbox_parts[pl_hb_idx].h * Graphics.pixelart_px_sz;
				Player_hbox_part.x = Ufo->pos_x + (Ufo->Hitbox_parts[pl_hb_idx].x * Graphics.pixelart_px_sz);
				Player_hbox_part.y = Ufo->pos_y + (Ufo->Hitbox_parts[pl_hb_idx].y * Graphics.pixelart_px_sz);

				if(!Ufo->has_custom_hitbox)
				{
					Player_hbox_part.w /= Graphics.pixelart_px_sz;
					Player_hbox_part.h /= Graphics.pixelart_px_sz;
				}
				for(std::size_t en_hb_idx = 0; en_hb_idx < Enemies[en_idx]->Hitbox_parts.size(); en_hb_idx++)
				{
					Enemy_hbox_part.w = Enemies[en_idx]->Hitbox_parts[en_hb_idx].w * Graphics.pixelart_px_sz;
					Enemy_hbox_part.h = Enemies[en_idx]->Hitbox_parts[en_hb_idx].h * Graphics.pixelart_px_sz;
					Enemy_hbox_part.x = Enemies[en_idx]->pos_x + (Enemies[en_idx]->Hitbox_parts[en_hb_idx].x * Graphics.pixelart_px_sz);
					Enemy_hbox_part.y = Enemies[en_idx]->pos_y + (Enemies[en_idx]->Hitbox_parts[en_hb_idx].y * Graphics.pixelart_px_sz);

					if(!Enemies[en_idx]->has_custom_hitbox)
					{
						Enemy_hbox_part.w /= Graphics.pixelart_px_sz;
						Enemy_hbox_part.h /= Graphics.pixelart_px_sz;
					}
					if(SDL_HasIntersection(&Player_hbox_part, &Enemy_hbox_part))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Level::set_model_borders(Entity& Entity)
{
	Entity.min_x = Entity.min_y = 0;
	Entity.max_x = width - Entity.Geometry.w;
	Entity.max_y = height - Entity.Geometry.h;
}

void Level::check_entity_pos(Entity& Entity)
{
	// If the model is out of the level, it will be moved to the mirrored place.
	if(Entity.pos_x < Entity.min_x)
	{
		Entity.pos_x = Entity.max_x;
	}
	else if(Entity.pos_x > Entity.max_x)
	{
		Entity.pos_x = Entity.min_x;
	}
	else if(Entity.pos_y < Entity.min_y)
	{
		Entity.pos_y = Entity.max_y;
	}
	else if(Entity.pos_y > Entity.max_y)
	{
		Entity.pos_y = Entity.min_y;
	}
}

bool Level::render(Graphics& Graphics)
{
	if(!Bg->tile_and_render(Graphics))
	{
		return false;
	}
	for(std::size_t idx = 0; idx < enemies_amount; idx++)
	{
		if(!Enemies[idx]->render(Graphics))
		{
			return false;
		}
		Enemies[idx]->move(Graphics, -Enemies[idx]->max_speed, 0.0);
	}
	if(!Ufo->render(Graphics))
	{
		return false;
	}
	return true;
}
