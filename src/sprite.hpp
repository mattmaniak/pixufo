#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <array>
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "error.hpp"
#include "graphics.hpp"
#include "os_env.hpp"

#define FRAMES_AMOUNT 6

class Sprite
{
public:
    const std::string name;

    std::array<SDL_Texture*, FRAMES_AMOUNT> textures;
    std::size_t                             current_frame_idx;

    SDL_Rect geometry; // Textures's position and size.
    double   pos_x;    // Theoretical (virtual) positions.
    double   pos_y;

    Sprite(Graphics&, const std::string, const Uint32);
    virtual ~Sprite();

    void         move(Graphics&, const double, const double);
    void         animate(const Graphics&);
    virtual bool render(Graphics&);

private:
    const Uint32 current_frame_start_time_ms_;
    Uint32       current_frame_elapsed_time_ms_;

    bool load_textures_(Graphics&);
};

#endif
