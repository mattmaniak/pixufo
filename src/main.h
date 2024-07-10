// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef MAIN_H_
#define MAIN_H_

#include "./error.h"
#include "./font.h"
#include "./graphics.h"
#include "./sprite.h"
#include "./menu.h"
#include "./level.h"
#include "./player.h"
#include "./state.h"

class Game {
 public:
  Game();
  ~Game();

  State get_state();

  bool level_loop();
  bool main_menu_loop();
  bool credits_menu_loop();
  bool pause_menu_loop();


 private:
  State     _state;
  Graphics* _graphics;
  Level*    _level;
};

#endif  // MAIN_H_
