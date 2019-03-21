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

#define MIN_ENEMIES_AMOUNT 10
#define MAX_ENEMIES_AMOUNT 20

#define MAX_ENEMY_HIDDEN_TIMEOUT_MS 3000

class Level: public Scene
{
public:
	unsigned int         score_points;

	Player*              Ufo;
	std::vector<Entity*> Enemies;
	std::size_t          enemies_amount;

	Level(Graphics&, const std::string, const unsigned int);
	~Level();

	void reset();
	void set_entities_borders(Graphics&);
	bool check_player_collision(); // Checks the basic models' rects.
	void check_player_pos();
	void check_enemies_pos(Graphics&);
	bool render(Graphics&);

private:
	void set_model_borders(Graphics&, Entity&);
	bool check_advanced_player_collision(const std::size_t);
	void randomize_enemies_amount();
	void randomize_enemy_type(Graphics&);
};

#endif
