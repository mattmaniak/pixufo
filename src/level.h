// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include <memory>
#include <string>
#include <vector>

#include "./error.h"
#include "./graphics.h"
#include "./scene.h"
#include "./entity.h"
#include "./player.h"

#define MIN_NEBULAS_NUMBER 15
#define MAX_NEBULAS_NUMBER 20

#define NEBULA_HIDDEN_TIMEOUT_MS 500  // Time when the enemy is hidden.

class Level: public Scene {
 public:
  unsigned int score_points;
  Player*      Ufo;

  Level(Graphics&, std::string, unsigned int);
  ~Level();

  void reset();
  void adjust_enemy_border(Graphics&);
  void check_ufo_pos();
  bool check_ufo_collision();  // Checks the basic models' rects.
  void check_enemies_pos(Graphics&);
  bool render(Graphics&);

 private:
  std::vector<Entity*> _nebulas;
  std::size_t          _nebulas_number;

  void _adjust_enemies_borders(Graphics&, Entity&);
  void _randomize_enemies_number();
  void _randomize_enemy_type(Graphics&);
  bool _check_advanced_ufo_collision(std::size_t);
  void _randomize_enemies_pos();
};

#endif  // SRC_LEVEL_H_
