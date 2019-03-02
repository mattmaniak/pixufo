#include "level.hpp"

Level::Level(Graphics& Graphics, const std::string bg_name,
             const unsigned int passed_enemies_amount):
Scene(Graphics, bg_name), enemies_amount(passed_enemies_amount)
{
	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	Ufo = new Player(Graphics);
	if(!Ufo->is_initialized)
	{
		is_initialized = false;
		return;
	}
	set_model_borders(*Ufo);

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(std::size_t idx = 0; idx < enemies_amount; idx++) // Create all enemies.
	{
		// Enemies.push_back(new Entity(Graphics, "nebula_medium", 50.0, 120));
		Enemies.push_back(new Entity(Graphics, "nebula_wasp", 000.0, 100));

		if(!Enemies[idx]->is_initialized)
		{
			is_initialized = false;
			return;
		}
		set_model_borders(*Enemies[idx]);
		Enemies[idx]->randomize_initial_pos();
	}
	is_initialized = true;
}

Level::~Level()
{
	delete Ufo;

	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
	Enemies.clear();
}

void Level::reset()
{
	Ufo->Movement[horizontal]->elapsed_time_s = 0.0;
	Ufo->Movement[vertical]->elapsed_time_s   = 0.0;

	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(std::size_t idx = 0; idx < enemies_amount; idx++)
	{
		Enemies[idx]->randomize_initial_pos();
	}
}

void Level::set_entities_borders(Graphics& Graphics)
{
	width  = Graphics.Display.w;
	height = Graphics.Display.h;

	set_model_borders(*Ufo);

	for(std::size_t idx = 0; idx < enemies_amount; idx++)
	{
		set_model_borders(*Enemies[idx]);
	}
}

void Level::set_model_borders(Sprite& Sprite)
{
	Sprite.min_x = Sprite.min_y = 0;
	Sprite.max_x = width - Sprite.Geometry.w;
	Sprite.max_y = height - Sprite.Geometry.h;
}
