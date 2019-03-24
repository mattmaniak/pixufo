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

#define NEBULA_HIDDEN_TIMEOUT_MS 3000 // Time when the enemy is hidden.

class Level: public Scene
{
public:
	unsigned int score_points;
	Player*      Ufo;

	Level(Graphics&, const std::string, const unsigned int);
	~Level();

	void reset();
	void set_entities_borders(Graphics&);
	bool check_player_collision(); // Checks the basic models' rects.
	void check_player_pos();
	void check_enemies_pos(Graphics&);
	bool render(Graphics&);

private:
	std::vector<Entity*> Nebulas_;
	std::size_t          nebulas_amount_;

	void set_model_borders_(Graphics&, Entity&);
	bool check_advanced_player_collision_(const std::size_t);
	void randomize_nebulas_amount_();
	void randomize_nebula_type_(Graphics&);
};

#endif
