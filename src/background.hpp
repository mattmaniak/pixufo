#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <limits>
#include "sprite.hpp"

class Background: public Sprite
{
public:
	Background(Graphics&, const std::string);

	bool tile_and_render(Graphics&); // Of course infinite.

private:
	void inf_scroll_();
};

#endif
