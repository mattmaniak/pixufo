// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "./error.h"

void error::show_box(const std::string message) {
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PixUfo Error",
                               message.c_str(), nullptr) != SDL2_SUCCESS) {
    // Poor...
    std::cerr << "Unable to show the error message box." << std::endl;
  }
}

error::Exception_box::Exception_box(const std::string& what_arg):
std::runtime_error(what_arg) {
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "PixUfo Exception",
                               what_arg.c_str(), nullptr) != SDL2_SUCCESS) {
    // Poor...
    std::cerr << "Unable to show the error message box." << std::endl;
  }
}
