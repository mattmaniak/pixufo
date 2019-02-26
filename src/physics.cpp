#include "physics.hpp"

void physics::check_model_pos(Model& Model)
{
	// If the model is out of the level, it will be moved to the mirrored place.
	if(Model.pos_x < Model.min_x)
	{
		Model.pos_x = Model.max_x;
	}
	else if(Model.pos_x > Model.max_x)
	{
		Model.pos_x = Model.min_x;
	}
	else if(Model.pos_y < Model.min_y)
	{
		Model.pos_y = Model.max_y;
	}
	else if(Model.pos_y > Model.max_y)
	{
		Model.pos_y = Model.min_y;
	}
}

bool physics::check_player_collision(Level& Level)
{
	for(std::size_t idx = 0; idx < Level.enemies_amount; idx++)
	{
		if(SDL_HasIntersection(&Level.Ufo->Geometry,
		                       &Level.Enemies[idx]->Geometry) == SDL_TRUE)
		{
			return true;
		}
	}
	return false;
}
