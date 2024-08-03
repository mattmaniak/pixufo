// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "player.h"

Player::Player(Graphics& graphics): Entity(graphics, "ufo", 110.0, 0) {
  horizontal_speed  = 0.0;
  vertical_speed    = 0.0;
  horizontal_step_  = 0.0;
  vertical_step_    = 0.0;
  directions_number = 0;

  Movements.insert(std::make_pair("horizontal", new player::Movement));
  Movements.insert(std::make_pair("vertical",   new player::Movement));
}

Player::~Player() {
  delete Movements["horizontal"];
  delete Movements["vertical"];

  Movements.clear();
}

bool Player::SteerUsingKeyboard(Graphics& graphics, State& state) {
  SDL_Event    input_event;
  const Uint8* keys;

  keys = SDL_GetKeyboardState(nullptr);
  SDL_PollEvent(&input_event);

  directions_number = 0;

  switch (input_event.type) {
    case SDL_QUIT:
      return false;
  }
  if (keys[SDL_SCANCODE_LEFT]) {
    Movements["horizontal"]->CountInertiaRatio(graphics, kLeft);
  }
  if (keys[SDL_SCANCODE_RIGHT]) {
    Movements["horizontal"]->CountInertiaRatio(graphics, kRight);
  }
  if (keys[SDL_SCANCODE_UP]) {
    Movements["vertical"]->CountInertiaRatio(graphics, kUp);
  }
  if (keys[SDL_SCANCODE_DOWN]) {
    Movements["vertical"]->CountInertiaRatio(graphics, kDown);
  }
  if (keys[SDL_SCANCODE_ESCAPE]) {
    state = kPauseMenu;
  }

  if ((horizontal_speed != 0.0f) && (vertical_speed != 0.0f)) {
    directions_number = 2;
  }
  Movements["horizontal"]->Move(graphics, *this);
  Movements["vertical"]->Move(graphics, *this);

  return true;
}

void Player::CenterOnDisplay(unsigned int screen_width,
                             unsigned int screen_height) {
  transform_.x = pos_x_ = (screen_width  - transform_.w) / 2;
  transform_.y = pos_y_ = (screen_height - transform_.h) / 2;
}

player::Movement::Movement(): max_time_s_(0.6), keypress_time_s_(0.0) {}

void player::Movement::CountInertiaRatio(Graphics& graphics,
                                         MovementDirection passed_direction) {
  direction_ = passed_direction;

  switch (direction_) {
  case kLeft:
    if ((keypress_time_s_ - graphics.delta_time_s) >= -max_time_s_) {
      keypress_time_s_ -= graphics.delta_time_s;
    }
    break;

  case kRight:
    if ((keypress_time_s_ + graphics.delta_time_s) <= max_time_s_) {
      keypress_time_s_ += graphics.delta_time_s;
    }
    break;

  case kUp:
    if ((keypress_time_s_ - graphics.delta_time_s) >= -max_time_s_) {
      keypress_time_s_ -= graphics.delta_time_s;
    }
    break;

  case kDown:
    if ((keypress_time_s_ + graphics.delta_time_s) <= max_time_s_) {
      keypress_time_s_ += graphics.delta_time_s;
    }
  }
}

void player::Movement::Move(Graphics& graphics, Player& player_) {
  double vector_length = std::sqrt(std::pow(player_.horizontal_speed, 2.0)
                         + std::pow(player_.vertical_speed, 2.0))
                         / player_.max_speed_;

  switch (direction_) {
  case kLeft:
  case kRight:
    player_.horizontal_speed = player_.max_speed_
                               * (keypress_time_s_ / max_time_s_);
    player_.horizontal_step_ = player_.horizontal_speed * graphics.delta_time_s
                               * graphics.pixelart_px_size_;
    break;

  case kUp:
  case kDown:
    player_.vertical_speed = player_.max_speed_
                             * (keypress_time_s_ / max_time_s_);
    player_.vertical_step_ = player_.vertical_speed * graphics.delta_time_s
                             * graphics.pixelart_px_size_;
  }

  // Prevents diagonal speed-ups.
  if ((player_.directions_number == 2) && (vector_length > 1.0)) {
    player_.horizontal_step_ /= vector_length;
    player_.vertical_step_   /= vector_length;
  }
  switch (direction_) {
  case kLeft:
  case kRight:
    player_.pos_x_ += player_.horizontal_step_;
    break;

  case kUp:
  case kDown:
    player_.pos_y_ += player_.vertical_step_;
  }
}
