#include "level.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "entity.hpp"
#include "background.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Level::Level(Graphics* Graphics, const std::string bg_name,
             const unsigned int passed_enemies_amount):
             enemies_amount(passed_enemies_amount), width(Graphics->Display.w),
             height(Graphics->Display.h)
{
	Ufo = new Player(Graphics, "ufo", 100.0f);
	if(!Ufo->initialized)
	{
		initialized = false;
		return;
	}
	set_model_borders(Graphics, Ufo);

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	Space_bg = new Background(Graphics, bg_name);
	if(!Space_bg->initialized)
	{
		initialized = false;
		return;
	}

	for(std::size_t idx = 0; idx < enemies_amount; idx++) // Create all enemies.
	{
		Enemies.push_back(new Entity(Graphics, "nebula_medium", 50.0f, 120));

		if(!Enemies[idx]->initialized)
		{
			initialized = false;
			return;
		}
		set_model_borders(Graphics, Enemies[idx]);
		Enemies[idx]->randomize_initial_pos();
	}
	initialized = true;
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

void Level::set_model_borders(Graphics* Graphics, Model* Model)
{
	Model->min_x = Graphics->pixelart_px_sz() - Model->Geometry.w;
	Model->max_x = width - Graphics->pixelart_px_sz();
	Model->min_y = Graphics->pixelart_px_sz() - Model->Geometry.h;
	Model->max_y = height - Graphics->pixelart_px_sz();
}
