#include "camera.hpp"
#include "models.hpp"
#include "level.hpp"

Camera::Camera(): pos_x(0.0f), pos_y(0.0f)
{

}

void Camera::move_entities(Level* Level, Model_player* Player,
                           Model_background* Background, Model_enemy* Enemy)
{
	std::cout << "Player: " << Player->pos_x << ' ' << Player->pos_y << std::endl;
	std::cout << "Enemy: " << Enemy->pos_x << ' ' << Enemy->pos_y << std::endl;

	const float player_to_background_speed = 2.0f;

	pos_x = Player->pos_x - Player->Geometry.x;
	pos_y = Player->pos_y - Player->Geometry.y;

	// std::cout << "Camera: " << pos_x << ' ' << pos_y << std::endl;

	// TODO
	Enemy->pos_x = -pos_x; // Player->Geometry.x - Player->pos_x;
	Enemy->pos_y = -pos_y; // Player->Geometry.y - Player->pos_y;

	// Background->pos_x = -pos_x / player_to_background_speed;
	// Background->pos_y = -pos_y / player_to_background_speed;
}
