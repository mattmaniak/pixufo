#include "error.hpp"

void error::show_box(std::string message)
{
	if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PixUfo error",
	                         message.c_str(), nullptr) != SDL2_SUCCESS)
	{

	}
	// TODO: TERMINAL ERROR.
}
