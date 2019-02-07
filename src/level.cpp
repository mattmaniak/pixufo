#include "level.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "enemy.hpp"
#include "background.hpp"
#include "player.hpp"
#include "levitation.hpp"

Level::Level(Graphics* Graphics, const std::string bg_name):
             width(Graphics->Screen.w), height(Graphics->Screen.h)
{
	enemies_amount = 1;

	Ufo = new Player(Graphics, "ufo", 100.0f);
	if(!Ufo->initialized)
	{
		error::show_box("Can't initialize the player's model.");
		initialized = false;
		return;
	}
	Ufo->min_x = Ufo->pixelart_pixel_sz() - Ufo->Geometry.w;
	Ufo->max_x = width - Ufo->pixelart_pixel_sz();
	Ufo->min_y = Ufo->pixelart_pixel_sz() - Ufo->Geometry.h;
	Ufo->max_y = height - Ufo->pixelart_pixel_sz();

	Player_levitation = new Levitation;

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (Graphics->Screen.w - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (Graphics->Screen.h - Ufo->Geometry.h) / 2;

	Space = new Background(Graphics, bg_name);
	if(!Space>initialized)
	{
		error::show_box("Can't initialize the background's model.");
		initialized = false;
		return;
	}

	// Create all enemies.
	for(size_t idx = 0; idx < enemies_amount; idx++)
	{
		Enemies.push_back(new Enemy(Graphics, "nebula_big", 50.0f));

		if(!Enemies[idx]->initialized)
		{
			error::show_box("Can't initialize the enemy's model.");
			initialized = false;
			return;
		}
	}
	initialized = true;
}

Level::~Level()
{
	delete Ufo;
	delete Player_levitation;
	delete Space;

	for(size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
}
