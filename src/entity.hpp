#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <random>
#include "sprite.hpp"

class Entity: public Sprite // Just sprite but more physical - with hitbox.
{
public:
	int min_x;
	int max_x;
	int min_y;
	int max_y;

	Uint32 hidden_timeout_ms;

	const double          max_speed; // Pixel position move in a one second.
	double                step;      // Pixel position move in a one frame.
	std::vector<SDL_Rect> Hitbox_parts;

	Entity(Graphics&, const std::string, const double, const Uint32);

	bool load_hitbox(Graphics&);
	void randomize_initial_pos();
	bool render(Graphics&);

private:

};

#endif
