#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "font.hpp"

class Button: public Font
{
public:
	const unsigned int idx;

	Button(Graphics&, const std::string, const int, const unsigned int);
};

#endif
