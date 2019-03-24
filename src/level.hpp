#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <memory>
#include <vector>
#include "error.hpp"
#include "graphics.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "player.hpp"

#define MIN_NEBULAS_AMOUNT 15
#define MAX_NEBULAS_AMOUNT 20

#define NEBULA_HIDDEN_TIMEOUT_MS 2000 // Time when the enemy is hidden.

class Level: public Scene
{
public:
	unsigned int score_points;
	Player*      Ufo;

	Level(Graphics&, const std::string, const unsigned int);
	~Level();

	void reset();
	void set_entities_borders(Graphics&);
	void check_ufo_pos();
	bool check_ufo_collision(); // Checks the basic models' rects.
	void check_nebulas_pos(Graphics&);
	bool render(Graphics&);

private:
	std::vector<Entity*> Nebulas_;
	std::size_t          nebulas_amount_;

	void set_entities_borders_(Graphics&, Entity&);
	void randomize_nebulas_amount_();
	void randomize_nebula_type_(Graphics&);
	bool check_advanced_ufo_collision_(const std::size_t);
};

#endif
