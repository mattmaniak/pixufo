#include "level.hpp"

Level::Level(Graphics* Graphics, const std::string bg_name,
             const unsigned int passed_enemies_amount):
             enemies_amount(passed_enemies_amount), width(Graphics->Display.w),
             height(Graphics->Display.h)
{
	Ufo = new Player(Graphics, "ufo", 100.0f);
	if(!Ufo->is_initialized)
	{
		is_initialized = false;
		return;
	}
	set_model_borders(Ufo);

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	Space_bg = new Background(Graphics, bg_name);
	if(!Space_bg->is_initialized)
	{
		is_initialized = false;
		return;
	}

	for(std::size_t idx = 0; idx < enemies_amount; idx++) // Create all enemies.
	{
		// Enemies.push_back(new Entity(Graphics, "nebula_medium", 50.0f, 120));
		Enemies.push_back(new Entity(Graphics, "nebula_wasp", 70.0f, 100));

		if(!Enemies[idx]->is_initialized)
		{
			is_initialized = false;
			return;
		}
		set_model_borders(Enemies[idx]);
		Enemies[idx]->randomize_initial_pos();
	}
	is_initialized = true;
}

Level::~Level()
{
	delete Ufo;
	delete Space_bg;

	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
	Enemies.clear();
}

void Level::reset()
{
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	for(std::size_t idx = 0; idx < enemies_amount; idx++)
	{
		Enemies[idx]->randomize_initial_pos();
	}
}

void Level::set_model_borders(Model* Model)
{
	Model->min_x = Model->min_y = 0;
	Model->max_x = width - Model->Geometry.w;
	Model->max_y = height - Model->Geometry.h;
}
