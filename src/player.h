// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <array>
#include <cmath>
#include <map>
#include <string>
#include <utility>

#include "entity.h"
#include "graphics.h"
#include "menu.h"
#include "state.h"

#define AXES_NUMBER 2

namespace player {
class Movement;
}

class Player: public Entity {
 public:
  double horizontal_speed;
  double vertical_speed;
  double horizontal_step;
  double vertical_step;

  std::size_t                              directions_number;
  std::map<std::string, player::Movement*> Movements;

  explicit Player(Graphics&);
  ~Player();

  bool SteerUsingKeyboard(Graphics&, State&);
  void CenterOnDisplay(unsigned int, unsigned int);
};

enum dir {
  left,
  right,
  up,
  down
};

namespace player {
class Movement {
 public:
  dir          direction;
  const double max_time_s;
  double       keypress_time_s;

  Movement();

  void count_ratio(Graphics&, dir);
  void Move(Graphics&, Player&);
};
}  // namespace player

#endif  // SRC_PLAYER_H_
