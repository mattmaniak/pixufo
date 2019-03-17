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

class Level: public Scene
{
public:
	// std::unique_ptr<Player> Ufo;
	Player*              Ufo;
	std::vector<Entity*> Enemies;
	std::size_t          enemies_amount;

	Level(Graphics&, const std::string, const unsigned int);
	~Level();

	void reset();
	void set_entities_borders(Graphics&);
	bool check_player_collision(Graphics&);
	void check_entity_pos(Entity&);
	bool render(Graphics&);

private:
	void set_model_borders(Graphics&, Entity&);
};

#endif
