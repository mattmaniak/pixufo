#include "level.hpp"

Level::Level(Graphics& Graphics, const std::string bg_name,
             const unsigned int passed_enemies_amount):
Scene(Graphics, bg_name), enemies_amount(passed_enemies_amount)
{
	const double size_to_screen_width_ratio = 1.0;

	width  = Graphics.Display.w * size_to_screen_width_ratio;
	height = Graphics.Display.h * size_to_screen_width_ratio;

	try
	{
		Ufo = new Player(Graphics);
	}
	catch(...)
	{
		throw std::runtime_error("");
	}
	set_model_borders(Graphics, *Ufo);

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(std::size_t idx = 0; idx < enemies_amount; idx++) // Create all enemies.
	{
		try
		{
			// Enemies.push_back(new Entity(Graphics, "nebula_big", 30.0, 180));
			Enemies.push_back(new Entity(Graphics, "nebula_medium", 60.0, 100));
		}
		catch(...)
		{
			throw std::runtime_error("");
		}
		set_model_borders(Graphics, *Enemies[idx]);
		Enemies[idx]->randomize_initial_pos();
	}
}

Level::~Level()
{
	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
	delete Ufo;
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

	set_model_borders(Graphics, *Ufo);

	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		set_model_borders(Graphics, *Enemies[idx]);
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
			for(std::size_t pl_hb_idx = 0; pl_hb_idx < Ufo->Hitbox_parts.size();
			    pl_hb_idx++)
			{
				Player_hbox_part.w = Ufo->Hitbox_parts[pl_hb_idx].w;
				Player_hbox_part.h = Ufo->Hitbox_parts[pl_hb_idx].h;
				Player_hbox_part.x = Ufo->pos_x + (Ufo->Hitbox_parts[pl_hb_idx].x);
				Player_hbox_part.y = Ufo->pos_y + (Ufo->Hitbox_parts[pl_hb_idx].y);

				for(std::size_t en_hb_idx = 0;
				    en_hb_idx < Enemies[en_idx]->Hitbox_parts.size();
				    en_hb_idx++)
				{
					Enemy_hbox_part.w = Enemies[en_idx]->Hitbox_parts[en_hb_idx].w;
					Enemy_hbox_part.h = Enemies[en_idx]->Hitbox_parts[en_hb_idx].h;
					Enemy_hbox_part.x = Enemies[en_idx]->pos_x + (Enemies[en_idx]->Hitbox_parts[en_hb_idx].x);
					Enemy_hbox_part.y = Enemies[en_idx]->pos_y + (Enemies[en_idx]->Hitbox_parts[en_hb_idx].y);

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

void Level::set_model_borders(Graphics& Graphics, Entity& Entity)
{
	Entity.min_x = Graphics.pixelart_px_sz - Entity.Geometry.w;
	Entity.min_y = Graphics.pixelart_px_sz - Entity.Geometry.h;
	Entity.max_x = width - Graphics.pixelart_px_sz;
	Entity.max_y = height - Graphics.pixelart_px_sz;
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
	for(auto& Enemy: Enemies)
	{
		if(!Enemy->render(Graphics))
		{
			return false;
		}
		Enemy->move(Graphics, -Enemy->max_speed, 0.0);
	}
	if(!Ufo->render(Graphics))
	{
		return false;
	}
	SDL_RenderPresent(Graphics.Renderer);

	return true;
}
