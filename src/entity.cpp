#include "entity.hpp"

Entity::Entity(Graphics* Graphics, const std::string name,
               const float passed_speed, const bool passed_animated):
Model(Graphics, name, passed_speed, passed_animated)
{

}

void Entity::randomize_initial_pos()
{
	pos_x = std::rand() % static_cast<int>((max_x - min_x + 1.0f) + min_x);
	pos_y = std::rand() % static_cast<int>((max_y - min_y + 1.0f) + min_y);
}
