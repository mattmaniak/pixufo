#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL2/SDL.h>
#include <vector>

class Background;
class Enemy;
class Planet;
class Player;

namespace camera
{
	void move_entities(Player* Player, Background* Background, Enemy* enemy);
}

#endif
