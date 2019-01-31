#include "level.hpp"
#include "error.hpp"
#include "graphics.hpp"
#include "model.hpp"
#include "levitation.hpp"

Level::Level(Graphics* Graphics, const std::string bg_name):
             width(Graphics->Screen.w), height(Graphics->Screen.h)
{
	enemies_amount = 1;

	Player = new model::Player(Graphics, "ufo", 100.0f);
	if(!Player->initialized)
	{
		error::show_box("Can't initialize the player's model.");
		initialized = false;
		return;
	}
	Player_levitation = new Levitation;

	// Set the player's default position;
	Player->Geometry.x = Player->pos_x = (Graphics->Screen.w - Player->Geometry.w) / 2;
	Player->Geometry.y = Player->pos_y = (Graphics->Screen.h - Player->Geometry.h) / 2;

	Background = new model::Background(Graphics, bg_name);
	if(!Background->initialized)
	{
		error::show_box("Can't initialize the background's model.");
		initialized = false;
		return;
	}
	initialized = true;

	// Create all enemies.
	for(size_t idx = 0; idx < enemies_amount; idx++)
	{
		Enemies.push_back(new model::Enemy(Graphics, "nebula_big", 50.0f));

		if(!Enemies[idx]->initialized)
		{
			error::show_box("Can't initialize the enemy's model.");
			initialized = false;
			return;
		}
	}
}

Level::~Level()
{
	delete Player;
	delete Player_levitation;
	delete Background;

	for(size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
}
