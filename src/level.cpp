#include "level.hpp"
#include "model.hpp"
#include "graphics.hpp"
#include "error.hpp"

Level::Level(Graphics* Graphics, const std::string bg_name):
             width(Graphics->Screen.w), height(Graphics->Screen.h)
{
	// TODO: VECTOR OF POINTERS.
	Player = new model::Player(Graphics, "ufo", 500.0f);
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

	model::Enemy* Nebula_big = new model::Enemy(Graphics, "nebula_big", 100.0f);
	Enemies.push_back(Nebula_big);

	for(size_t idx = 0; idx < Enemies.size(); idx++)
	{
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
