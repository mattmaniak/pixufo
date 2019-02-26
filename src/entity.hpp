#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <random>

#include "model.hpp"

class Entity: public Model
{
	public:
	Entity(Graphics&, const std::string, const double, const Uint32);

	void randomize_initial_pos();
};

#endif
