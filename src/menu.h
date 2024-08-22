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
#include "font.h"
#include "graphics.h"
#include "scene.h"
#include "state.h"

#define PADDING (20.0 * graphics.pixelart_px_size_)

#define MAIN_FONT_SZ 50
#define TEXT_FONT_SZ 24

class Level;
class Player;

class Menu: public Scene {
 public:
  explicit Menu(Graphics&);
  ~Menu();

  bool         Render(Graphics&);
  virtual bool SteerUsingKeyboard(State&) = 0;

  bool                           contains_text_;
  bool                           selection_arrow_focused_;
  std::map<std::string, Sprite*> sprites_;
  std::size_t                    selected_button_idx_;
  std::vector<Font*>             buttons_;
  std::vector<Font*>             text_lines_;
};


class Main_menu: public Menu {
 public:
  explicit Main_menu(Graphics&);
  ~Main_menu();

  bool SteerUsingKeyboard(State&);
};

class Pause_menu: public Menu {
 public:
  explicit Pause_menu(Graphics&);
  ~Pause_menu();

  bool SteerUsingKeyboard(State&);
};

class Credits_menu: public Menu {
 public:
  explicit Credits_menu(Graphics&);
  ~Credits_menu();

  bool SteerUsingKeyboard(State&);
};

#endif  // SRC_MENU_H_
