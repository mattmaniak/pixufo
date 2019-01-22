#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>

// class Model_background;

class Level
{
	public:
	const unsigned int width;
	const unsigned int height;
	// Model_background   Background;

	Level(const std::string background_name);
};

#endif
