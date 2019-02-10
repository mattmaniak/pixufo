#include "level.hpp"
#include "error.hpp"
#include "rendering.hpp"
#include "enemy.hpp"
#include "background.hpp"
#include "player.hpp"
#include "slowdown.hpp"

Level::Level(Rendering* Rendering, const std::string bg_name):
             width(Rendering->Display.w), height(Rendering->Display.h),
             enemies_amount(0)
{
	Ufo = new Player(Rendering, "ufo", 100.0f);
	if(!Ufo->initialized)
	{
		initialized = false;
		return;
	}
	Ufo->min_x = Rendering->pixelart_pixel_sz() - Ufo->Geometry.w;
	Ufo->max_x = width - Rendering->pixelart_pixel_sz();
	Ufo->min_y = Rendering->pixelart_pixel_sz() - Ufo->Geometry.h;
	Ufo->max_y = height - Rendering->pixelart_pixel_sz();

	// Set the player's default position;
	Ufo->Geometry.x = Ufo->pos_x = (Rendering->Display.w - Ufo->Geometry.w) / 2;
	Ufo->Geometry.y = Ufo->pos_y = (Rendering->Display.h - Ufo->Geometry.h) / 2;

	Space = new Background(Rendering, bg_name);
	if(!Space>initialized)
	{
		initialized = false;
		return;
	}

	// Create all enemies.
	for(std::size_t enemy_idx = 0; enemy_idx < enemies_amount; enemy_idx++)
	{
		Enemies.push_back(new Enemy(Rendering, "nebula_big", 50.0f));

		if(!Enemies[enemy_idx]->initialized)
		{
			initialized = false;
			return;
		}
	}
	initialized = true;
}

Level::~Level()
{
	delete Ufo;
	delete Space;

	for(std::size_t enemy_idx = 0; enemy_idx < Enemies.size(); enemy_idx++)
	{
		delete Enemies[enemy_idx];
	}
	Enemies.clear();
}

void Level::check_player_pos()
{
	/* If the player is out of the level (display), it will be moved to the
	mirrored place. */
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
