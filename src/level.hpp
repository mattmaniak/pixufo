#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include "error.hpp"
#include "graphics.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "player.hpp"

class Level: public Scene
{
	public:
	// bool is_initialized;
	//
	// int width;
	// int height;
	//
	// Background*          Space_bg;
	Player*              Ufo;
	std::vector<Entity*> Enemies;
	std::size_t          enemies_amount;

	Level(Graphics&, const std::string, const unsigned int);
	~Level();

	void reset();
	void set_entities_borders(Graphics&);

	private:
	void set_model_borders(Sprite&);
};

#endif
