#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>

class Graphics;
class Model_background;

class Level
{
	public:
	bool     initialized;
	const int width;
	const int height;
	// Model_background   Background(dawdwad, awdaw);

	Level(Graphics* Graphics, const std::string background_name);
};

#endif
