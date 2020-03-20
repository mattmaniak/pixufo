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

#define NEBULA_HIDDEN_TIMEOUT_MS 500 // Time when the enemy is hidden.

class Level: public Scene
{
public:
    unsigned int score_points;
    Player*      Ufo;

    Level(Graphics&, const std::string, const unsigned int);
    ~Level();

    void reset();
    void adjust_enemy_border(Graphics&);
    void check_ufo_pos();
    bool check_ufo_collision(); // Checks the basic models' rects.
    void check_enemies_pos(Graphics&);
    bool render(Graphics&);

private:
    std::vector<Entity*> _enemies;
    std::size_t          _enemies_number;

    void _adjust_enemies_border(Graphics&, Entity&);
    void randomize_enemies_amount_();
    void randomize_enemy_type_(Graphics&);
    bool check_advanced_ufo_collision_(const std::size_t);
    void randomize_enemies_pos_();
};

#endif
