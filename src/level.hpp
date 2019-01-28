#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

class Graphics;

namespace model
{
	class Background;
	class Player;
	class Enemy;
}

class Level
{
	public:
	bool                       initialized;
	const int                  width;
	const int                  height;
	size_t                     enemies_amount;
	model::Player*             Player;
	model::Background*         Background;
	std::vector<model::Enemy*> Enemies;

	Level(Graphics* Graphics, const std::string bg_name);
	~Level();
};

#endif
