// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

#include <iostream>
#include <stdexcept>
#include <string>

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

#define SDL2_SUCCESS 0

namespace error {
void ShowBox(const std::string);

class Exception_box: public std::runtime_error {
 public:
  explicit Exception_box(const std::string&);
};
}

#endif  // SRC_ERROR_H_
