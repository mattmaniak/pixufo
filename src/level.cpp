#include "level.hpp"

Level::Level(Graphics& Graphics, const std::string bg_name,
             const unsigned int passed_enemies_amount):
Scene(Graphics, bg_name), score_points(0), enemies_amount(passed_enemies_amount)
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
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w)  / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

    randomize_enemies_amount();

	for(std::size_t idx = 0; idx < enemies_amount; idx++) // Create all enemies.
	{
		try
		{
			randomize_enemy_type(Graphics);
		}
		catch(...)
		{
			throw std::runtime_error("");
		}
		set_model_borders(Graphics, *Enemies[idx]);
	}
}

Level::~Level()
{
	for(std::size_t idx = 0; idx < enemies_amount; idx++)
	{
		delete Enemies[idx];
	}
	delete Ufo;
}

void Level::randomize_enemies_amount()
{
	std::mt19937 prng;
	// prng.seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type>
	distributor_enemies(MIN_ENEMIES_AMOUNT, MAX_ENEMIES_AMOUNT);

	enemies_amount = distributor_enemies(prng);
}

void Level::randomize_enemy_type(Graphics& Graphics)
{
	const int enemies_types_pool = 10;

	std::mt19937 prng;
	prng.seed(std::random_device()());

	std::uniform_int_distribution<>
	distributor_enemy_type(0, enemies_types_pool - 1);

	try
	{
		switch(distributor_enemy_type(prng))
		{
		case 0:
		case 1:
		case 2:
		case 3:
			Enemies.push_back(new Entity(Graphics, "nebula_wasp", 160.0, 80));
			break;

		case 4:
		case 5:
		case 6:
			Enemies.push_back(new Entity(Graphics, "nebula_medium", 120.0, 100));
			break;

		case 7:
		case 8:
			Enemies.push_back(new Entity(Graphics, "nebula_big", 90.0, 130));
			break;

	    case 9:
			Enemies.push_back(new Entity(Graphics, "nebula_umbrella", 50.0, 0));
	    }
	}
	catch(...)
	{
		std::runtime_error("");
	}
}

void Level::reset()
{
	Ufo->Movements["horizontal"]->keypress_time_s = 0.0;
	Ufo->Movements["vertical"]->keypress_time_s   = 0.0;

	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w)  / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(auto& Enemy: Enemies)
	{
		Enemy->randomize_initial_pos();
	}
}

void Level::set_entities_borders(Graphics& Graphics)
{
	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	for(auto& Enemy: Enemies)
	{
		set_model_borders(Graphics, *Enemy);
	}
	set_model_borders(Graphics, *Ufo);
}

bool Level::check_player_collision()
{
	for(std::size_t en_idx = 0; en_idx < Enemies.size(); en_idx++)
	{
		if(SDL_HasIntersection(&Ufo->Geometry, &Enemies[en_idx]->Geometry))
		{
			if(check_advanced_player_collision(en_idx))
			{
				return true;
			}
		}
	}
	return false;
}

bool Level::check_advanced_player_collision(const std::size_t en_idx)
{
	SDL_Rect Player_hbox_part;
	SDL_Rect Enemy_hbox_part;

	// Check the Player's hitbox part by Enemies' hitbox part.
	for(std::size_t pl_hb_idx = 0; pl_hb_idx < Ufo->Hitbox_parts.size();
	    pl_hb_idx++)
	{
		// Position the Player's hitbox part.
		Player_hbox_part.w = Ufo->Hitbox_parts[pl_hb_idx].w;
		Player_hbox_part.h = Ufo->Hitbox_parts[pl_hb_idx].h;
		Player_hbox_part.x = Ufo->pos_x + (Ufo->Hitbox_parts[pl_hb_idx].x);
		Player_hbox_part.y = Ufo->pos_y + (Ufo->Hitbox_parts[pl_hb_idx].y);

		for(std::size_t en_hb_idx = 0;
		    en_hb_idx < Enemies[en_idx]->Hitbox_parts.size(); en_hb_idx++)
		{
			// Position the Enemy's hitbox part.
			Enemy_hbox_part.w = Enemies[en_idx]->Hitbox_parts[en_hb_idx].w;
			Enemy_hbox_part.h = Enemies[en_idx]->Hitbox_parts[en_hb_idx].h;
			Enemy_hbox_part.x = Enemies[en_idx]->pos_x
			                    + (Enemies[en_idx]->Hitbox_parts[en_hb_idx].x);

			Enemy_hbox_part.y = Enemies[en_idx]->pos_y
			                    + (Enemies[en_idx]->Hitbox_parts[en_hb_idx].y);

			if(SDL_HasIntersection(&Player_hbox_part, &Enemy_hbox_part))
			{
				return true; // Collision.
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

void Level::check_enemies_pos(Graphics& Graphics)
{
	for(auto& Enemy: Enemies)
	{
		if((Enemy->pos_x < Enemy->min_x) || (Enemy->pos_x > Enemy->max_x))
		{
			Enemy->hidden_timeout_ms += Graphics.delta_time_s * 1000;
		}
		if(Enemy->hidden_timeout_ms > MAX_ENEMY_HIDDEN_TIMEOUT_MS)
		{
			Enemy->hidden_timeout_ms = 0;

			Enemy->randomize_initial_pos();
			Enemy->pos_x = Graphics.Display.w - Graphics.pixelart_px_sz;
		}
	}
}

void Level::check_player_pos()
{
	// If the model is out of the level, it will be moved to the mirrored place.
	if(Ufo->pos_x < Ufo->min_x)
	{
		Ufo->pos_x = Ufo->max_x;
	}
	else if(Ufo->pos_x > Ufo->max_x)
	{
		Ufo->pos_x = Ufo->min_x;
	}
	else if(Ufo->pos_y < Ufo->min_y)
	{
		Ufo->pos_y = Ufo->max_y;
	}
	else if(Ufo->pos_y > Ufo->max_y)
	{
		Ufo->pos_y = Ufo->min_y;
	}
}

bool Level::render(Graphics& Graphics)
{
	Font Score_font(Graphics, std::to_string(score_points), 30);
	Score_font.pos_x = Score_font.pos_y = PADDING / 2.0; // Left, upper corner.

	if(!Bg->tile_and_render(Graphics))
	{
		return false;
	}
	Bg->move(Graphics, -8.0, 0.0);

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
	if(!Score_font.render(Graphics))
	{
		return false;
	}
	SDL_RenderPresent(Graphics.Renderer);

	return true;
}
