#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "model.hpp"

class Background: public Model
{
	public:
	Background(Graphics&, const std::string);

	void inf_scroll();
};


#endif
