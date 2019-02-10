#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

class Rendering;
class Player_slowdown;

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
	std::size_t         enemies_amount;
	Player*             Ufo;
	Player_slowdown*    Player_levitation;
	Background*         Space;
	std::vector<Enemy*> Enemies;

	Level(Rendering* Rendering, const std::string bg_name);
	~Level();

	void check_player_pos(); // Move the player if out the level.
};

#endif
