#include "level.hpp"
#include "models.hpp"
#include "graphics.hpp"

Level::Level(Graphics* Graphics, const std::string background_name):
             width(Graphics->Screen.w), height(Graphics->Screen.w)
{
	Model_background Background(Graphics, background_name);
	if(!Background.initialized)
	{
		initialized = false;
		return;
	}
	initialized = true;
}
