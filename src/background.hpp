#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "model.hpp"

class Background: public Model
{
	public:
	Background(Graphics*, const std::string);

	void inf_scroll();
	void move(Graphics*, const float, const float);
};


#endif
