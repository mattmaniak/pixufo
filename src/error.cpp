#include "error.hpp"

void error::show_box(const std::string message)
{
	if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PixUfo error",
	                            message.c_str(), nullptr) != SDL2_SUCCESS)
	{
		// Poor...
		std::cerr << "Can't show the error message box." << std::endl;
	}
}
