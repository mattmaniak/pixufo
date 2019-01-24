#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>

class Graphics;
class Model_background;

class Level
{
	public:
	bool               initialized;
	const unsigned int width;
	const unsigned int height;
	// Model_background   Background;

	Level(Graphics* Graphics, const std::string background_name);
};

#endif
