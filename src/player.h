#ifndef PLAYER_H_
#define PLAYER_H_

#include <array>
#include <cmath>
#include <map>
#include <string>

#include "entity.h"
#include "graphics.h"
#include "menu.h"
#include "state.h"

#define AXES_AMOUNT 2

namespace player {
  class Movement;
}

class Player: public Entity {
public:
  double horizontal_speed;
  double vertical_speed;
  double horizontal_step;
  double vertical_step;

  std::size_t                              directions_amount;
  std::map<std::string, player::Movement*> Movements;

  Player(Graphics&);
  ~Player();

  bool keyboard_steering(Graphics&, State&);
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
    void move(Graphics&, Player&);
  };
}

#endif // PLAYER_H_
