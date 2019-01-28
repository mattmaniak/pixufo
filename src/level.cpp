#include "level.hpp"
#include "model.hpp"
#include "graphics.hpp"
#include "error.hpp"

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

	Background = new model::Background(Graphics, bg_name);
	if(!Background->initialized)
	{
		error::show_box("Can't initialize the background's model.");
		initialized = false;
		return;
	}
	initialized = true;

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
	delete Background;

	for(size_t idx = 0; idx < Enemies.size(); idx++)
	{
		delete Enemies[idx];
	}
}
