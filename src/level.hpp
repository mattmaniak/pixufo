#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

class Rendering;
class Slowdown;

class Background;
class Player;
class Enemy;
class Model;

class Level
{
	public:
	bool                initialized;
	const int           width;
	const int           height;
	size_t              enemies_amount;
	Player*             Ufo;
	Slowdown*           Player_levitation;
	Background*         Space;
	std::vector<Enemy*> Enemies;

	Level(Rendering* Rendering, const std::string bg_name);
	~Level();
};

#endif
