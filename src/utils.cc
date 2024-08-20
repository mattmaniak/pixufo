// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "utils.h"

template double utils::generate_pseudorandom_number(double, double);
template int    utils::generate_pseudorandom_number(int, int);

template<typename T>
T utils::generate_pseudorandom_number(T min, T max) {
  std::random_device device;
  std::mt19937 generator(device());

  if (std::is_same<T, double>()) {
    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(generator);
  } else if (std::is_same<T, int>()) {
    return generator() % static_cast<int>(max - min) + min;
  }
}
