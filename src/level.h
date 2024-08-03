// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include <memory>
#include <string>
#include <vector>

#include "error.h"
#include "graphics.h"
#include "scene.h"
#include "entity.h"
#include "player.h"

#define MIN_NEBULAS_NUMBER 15
#define MAX_NEBULAS_NUMBER 20
#define BACKGROUND_ABSOLUTE_HORIZONTAL_SPEED 8.0
#define BACKGROUND_TO_PLAYER_SPEED 0.5

#define NEBULA_HIDDEN_TIMEOUT_MS 500  // Time when the enemy is hidden.

class Level: public Scene {
 public:
  Level(Graphics&, std::string, unsigned int);
  ~Level();

  bool CheckPlayerCollision();  // Checks the basic models' rects.
  bool Render(Graphics&);
  void Reset();
  void AdjustAllEntitiesBorders(Graphics&);
  void CheckPlayerPos();
  void CheckEnemiesPosition(Graphics&);

  Player*      player_;
  unsigned int score_points_;

 private:
  bool CheckPlayerAdvancedCollision(std::size_t);
  void AdjustEntityBorders(Graphics&, Entity&);
  void RandomizeEnemiesNumber();
  void RandomizeEnemiesPosition();
  void RandomizeEnemyType(Graphics&);

  std::size_t          enemies_number_;
  std::vector<Entity*> enemies_;
};

#endif  // SRC_LEVEL_H_
