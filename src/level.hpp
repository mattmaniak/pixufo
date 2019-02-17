#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

class Graphics;
class Player_slowdown;

class Background;
class Player;
class Entity;
class Model;

class Level
{
	public:
	bool                 initialized;
	const unsigned int   width;
	const unsigned int   height;
	Background*          Space;

	Player*              Ufo;
	Player_slowdown*     Player_levitation;

	std::size_t          enemies_amount;
	std::vector<Entity*> Enemies;

	Level(Graphics* Graphics, const std::string bg_name);
	~Level();
};

#endif
