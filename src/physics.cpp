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
