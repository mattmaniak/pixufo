// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "scene.h"

Scene::Scene(Graphics& graphics, std::string bg_name): _Graphics(&graphics) {
  try {
    Bg = new Background(*_Graphics, bg_name);

    Bg->pos_x = _Graphics->Last_bg_transform.x;
    Bg->pos_y = _Graphics->Last_bg_transform.y;
  } catch (std::runtime_error) {
    throw std::runtime_error("");
  }
}

Scene::~Scene() {
  _Graphics->Last_bg_transform.x = Bg->transform.x;
  _Graphics->Last_bg_transform.y = Bg->transform.y;

  delete Bg;
}
