#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "model.hpp"

class Background: public Model
{
	public:
	Background(Graphics* Graphics, const std::string name);

	void inf_scroll();
	void move(Graphics* Graphics, const float offset_x,
              const float offset_y);
};


#endif
