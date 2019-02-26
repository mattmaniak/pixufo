#include "entity.hpp"

Entity::Entity(Graphics& Graphics, const std::string name,
               const double passed_speed,
               const Uint32 passed_single_frame_time_ms):
Model(Graphics, name, passed_speed, passed_single_frame_time_ms)
{

}

void Entity::randomize_initial_pos()
{
	std::mt19937 prng;
	prng.seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type>
	distributor_x(min_x, max_x);

	std::uniform_int_distribution<std::mt19937::result_type>
	distributor_y(min_y, max_y);

	pos_x = distributor_x(prng);
	pos_y = distributor_y(prng);
}
