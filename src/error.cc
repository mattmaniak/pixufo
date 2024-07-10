#include "./error.h"

void error::show_box(const std::string message)
{
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PixUfo error", message.c_str(), nullptr) != SDL2_SUCCESS) {
    // Poor...
    std::cerr << "Unable to show the error message box." << std::endl;
  }
}

error::Exception_box::Exception_box(const std::string& what_arg):
std::runtime_error(what_arg) {
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PixUfo exception error", what_arg.c_str(), nullptr) != SDL2_SUCCESS) {
    // Poor...
    std::cerr << "Unable to show the error message box." << std::endl;
  }
}
