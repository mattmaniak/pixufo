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
}  // namespace player

class Player: public Entity {
 public:
  explicit Player(Graphics&);
  ~Player();

  bool SteerUsingKeyboard(Graphics&, State&);
  void CenterOnDisplay(unsigned int, unsigned int);

  double                                   horizontal_speed_;
  double                                   horizontal_step_;
  double                                   vertical_speed_;
  double                                   vertical_step_;
  std::map<std::string, player::Movement*> Movements;
  std::size_t                              directions_number;
};

enum MovementDirection {
  kLeft,
  kRight,
  kUp,
  kDown
};

namespace player {
class Movement {
 public:
  MovementDirection direction_;
  const double      max_time_s_;
  double            keypress_time_s_;

  Movement();

  void CountInertiaRatio(Graphics&, MovementDirection);
  void Move(Graphics&, Player&);
};
}  // namespace player

#endif  // SRC_PLAYER_H_
