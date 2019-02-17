#include "level.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "entity.hpp"
#include "background.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Level::Level(Graphics* Graphics, const std::string bg_name):
             width(Graphics->Display.w), height(Graphics->Display.h),
             enemies_amount(2)
{
	Ufo = new Player(Graphics, "ufo", 100.0f);
	if(!Ufo->initialized)
	{
		initialized = false;
		return;
	}
	Ufo->min_x = Graphics->pixelart_px_sz() - Ufo->Geometry.w;
	Ufo->max_x = width - Graphics->pixelart_px_sz();
	Ufo->min_y = Graphics->pixelart_px_sz() - Ufo->Geometry.h;
	Ufo->max_y = height - Graphics->pixelart_px_sz();

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (width - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (height - Ufo->Geometry.h) / 2;

	Space = new Background(Graphics, bg_name);
	if(!Space->initialized)
	{
		initialized = false;
		return;
	}

	// Create all enemies.
	for(std::size_t idx = 0; idx < enemies_amount; idx++)
	{
		Enemies.push_back(new Entity(Graphics, "enemy_nebula_medium", 40.0f,
		                             true));

		if(!Enemies[idx]->initialized)
		{
			initialized = false;
			return;
		}
		Enemies[idx]->min_x = Graphics->pixelart_px_sz() - Enemies[idx]->Geometry.w;
		Enemies[idx]->max_x = width - Graphics->pixelart_px_sz();
		Enemies[idx]->min_y = Graphics->pixelart_px_sz() - Enemies[idx]->Geometry.h;
		Enemies[idx]->max_y = height - Graphics->pixelart_px_sz();

		Enemies[idx]->randomize_initial_pos();
	}
	initialized = true;
}

Level::~Level()
{
	delete Ufo;
	delete Space;

	for(std::size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
	Enemies.clear();
}
