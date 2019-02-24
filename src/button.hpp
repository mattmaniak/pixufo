#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "model.hpp"

class Button: public Model
{
	public:
	const unsigned int idx;

	Button(Graphics&, const std::string, const unsigned int);
};

#endif
