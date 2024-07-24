// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

#include "error.h"
#include "scene.h"
#include "graphics.h"
#include "font.h"
#include "state.h"

#define PADDING (20.0 * graphics.pixelart_px_sz)

#define MAIN_FONT_SZ 36  // Same as the meteor.bmp height.
#define TEXT_FONT_SZ 24

class Level;
class Player;

class Menu: public Scene {
 public:
  std::size_t                    selected_button_idx;
  bool                           selection_arrow_focused;
  std::vector<Font*>             buttons;
  std::map<std::string, Sprite*> Sprites;
  std::vector<Font*>             Text_lines;
  bool                           has_text;

  explicit Menu(Graphics&);
  ~Menu();

  bool         render(Graphics&);
  virtual bool keyboard_steering(State&) = 0;
};


class Main_menu: public Menu {
 public:
  explicit Main_menu(Graphics&);
  ~Main_menu();

  bool keyboard_steering(State&);
};

class Pause_menu: public Menu {
 public:
  explicit Pause_menu(Graphics&);
  ~Pause_menu();

  bool keyboard_steering(State&);
};

class Credits_menu: public Menu {
 public:
  explicit Credits_menu(Graphics&);
  ~Credits_menu();

  bool keyboard_steering(State&);
};

#endif  // SRC_MENU_H_
