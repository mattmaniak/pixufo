#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "model.hpp"

#define CURRENT_BUTTON_SHIFT 32

class Button: public Model
{
	public:
	const unsigned int idx;

	Button(Rendering* Rendering, const std::string name,
	       const unsigned int passed_idx);
};

#endif
