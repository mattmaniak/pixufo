#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include "error.hpp"
#include "graphics.hpp"
#include "entity.hpp"
#include "background.hpp"
#include "player.hpp"
#include "slowdown.hpp"

class Level
{
	public:
	bool                 is_initialized;

	Background*          Space_bg;
	Player*              Ufo;
	std::vector<Entity*> Enemies;
	std::size_t          enemies_amount;

	Level(Graphics&, const std::string, const unsigned int);
	~Level();

	void reset();

	private:
	const unsigned int width;
	const unsigned int height;

	void set_model_borders(Model*);
};

#endif
