#include "camera.hpp"
#include "model.hpp"

void camera::move_entities(Model_player* Player, Model_background* Background,
                           Model_enemy* Enemy)
{
	const float player_to_background_speed = 2.0f;

	Enemy->pos_x -= Player->pos_x;
	Enemy->pos_y -= Player->pos_y;

	Background->pos_x -= (Player->pos_x / player_to_background_speed);
	Background->pos_y -= (Player->pos_y / player_to_background_speed);

	Player->pos_x = 0.0f;
	Player->pos_y = 0.0f;
}
