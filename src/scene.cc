// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "scene.h"

Scene::Scene(Graphics& graphics, std::string bg_name): graphics_(&graphics) {
  try {
    bg_ = new Background(*graphics_, bg_name);

    bg_->pos_x_ = graphics_->last_bg_transform_.x;
    bg_->pos_y_ = graphics_->last_bg_transform_.y;
  } catch (std::runtime_error) {
    throw std::runtime_error("");
  }
}

Scene::~Scene() {
  graphics_->last_bg_transform_.x = bg_->transform_.x;
  graphics_->last_bg_transform_.y = bg_->transform_.y;

  delete bg_;
}
