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
	bool              is_initialized;
	const std::string name;

	std::array<SDL_Texture*, FRAMES_AMOUNT> Textures;
	std::size_t                             current_frame_idx;

	SDL_Rect Geometry; // Textures's position and size.
	double   pos_x;    // Theoretical (virtual) positions.
	double   pos_y;

	Sprite(Graphics&, const std::string, const Uint32);
	virtual ~Sprite();

	void         move(Graphics&, const double, const double);
	void         animate(const Graphics&);
	virtual bool render(Graphics&);

private:
	const Uint32 single_frame_time_ms;
	Uint32       frame_elapsed_time_ms;

	bool load_textures(Graphics&);
	bool load_animation(Graphics&);
};

#endif
