#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "model.hpp"

class Button: public Model
{
	public:
	const unsigned int idx;

	Button(Graphics* Graphics, const std::string name,
	       const unsigned int passed_idx);
};

#endif
