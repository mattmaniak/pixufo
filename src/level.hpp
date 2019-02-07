#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

class Graphics;
class Levitation;

class Background;
class Player;
class Enemy;

// namespace model
// {
// 	class Background;
// 	class Player;
// 	class Enemy;
// }

class Level
{
	public:
	bool                initialized;
	const int           width;
	const int           height;
	size_t              enemies_amount;
	Player*             Ufo;
	Levitation*         Player_levitation;
	Background*         Space;
	std::vector<Enemy*> Enemies;

	Level(Graphics* Graphics, const std::string bg_name);
	~Level();
};

#endif
