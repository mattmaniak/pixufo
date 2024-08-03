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
  unsigned int score_points_;
  Player*      player_;

  Level(Graphics&, std::string, unsigned int);
  ~Level();

  void Reset();
  void AdjustAllEntitiesBorders(Graphics&);
  void CheckPlayerPos();
  bool CheckPlayerCollision();  // Checks the basic models' rects.
  void CheckEnemiesPosition(Graphics&);
  bool Render(Graphics&);

 private:
  std::vector<Entity*> enemies_;
  std::size_t          enemies_number_;

  void AdjustEntityBorders(Graphics&, Entity&);
  void RandimizeEnemiesNumber();
  void RandimizeEnemyType(Graphics&);
  bool CheckPlayerAdvancedCollision(std::size_t);
  void RandomizeEnemiesPosition();
};

#endif  // SRC_LEVEL_H_
