#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <random>

#include "sprite.hpp"

class Entity: public Sprite
{
	public:
	Entity(Graphics&, const std::string, const double, const Uint32);

	void randomize_initial_pos();
};

#endif
