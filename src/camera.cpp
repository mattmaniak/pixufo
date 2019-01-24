#include "camera.hpp"
#include "models.hpp"
#include "level.hpp"

void camera::move_entities(Level* Level, Model_player* Player,
                           Model_background* Background, Model_enemy* Enemy)
{
	const float player_to_background_speed = 2.0f;

	// TODO
	Enemy->pos_x = Player->Geometry.x - Player->pos_x;
	Enemy->pos_y = Player->Geometry.y - Player->pos_y;

	std::cout << Player->pos_x << ' ' << Player->pos_y << std::endl;

	Background->pos_x = (Player->Geometry.x - Player->pos_x) / player_to_background_speed;
	Background->pos_y = (Player->Geometry.y - Player->pos_y) / player_to_background_speed;
}
