#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include <SDL2/SDL.h>
#include <vector>
#include "error.hpp"
#include "scene.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "state.hpp"

#define PADDING (20.0 * graphics.pixelart_px_sz)

#define MAIN_FONT_SZ 36 // Same as the meteor.bmp height.
#define TEXT_FONT_SZ 24

class Level;
class Player;

class Menu: public Scene
{
public:
    std::size_t                    selected_button_idx;
    bool                           selection_arrow_focused;
    std::vector<Font*>             buttons;
    std::map<std::string, Sprite*> Sprites;
    std::vector<Font*>             Text_lines;
    bool                           has_text;

    Menu(Graphics&);
    ~Menu();

    bool         render(Graphics&);
    virtual bool keyboard_steering(State&) = 0;
};


class Main_menu: public Menu
{
public:
    Main_menu(Graphics&);
    ~Main_menu();

    bool keyboard_steering(State&);
};

class Pause_menu: public Menu
{
public:
    Pause_menu(Graphics&);
    ~Pause_menu();

    bool keyboard_steering(State&);
};

class Credits_menu: public Menu
{
public:
    Credits_menu(Graphics&);
    ~Credits_menu();

    bool keyboard_steering(State&);
};

#endif
