#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL2/SDL.h>
#include <vector>

class Model_background;
class Model_enemy;
class Model_planet;
class Model_player;
class Level;

namespace camera
{
	void move_entities(Level* Level, Model_player* Player,
	                   Model_background* Background, Model_enemy* enemy);
}

class Camera
{
	public:
	float pos_x;
	float pos_y;
};

#endif
