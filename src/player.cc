// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "player.h"

Player::Player(Graphics& graphics): Entity(graphics, "ufo", 110.0, 0) {
  horizontal_speed  = 0.0;
  vertical_speed    = 0.0;
  horizontal_step   = 0.0;
  vertical_step     = 0.0;
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
  SDL_Event    Event;
  const Uint8* keys;

  keys = SDL_GetKeyboardState(nullptr);
  SDL_PollEvent(&Event);

  directions_number = 0;

  switch (Event.type) {
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
  transform.x = pos_x = (screen_width  - transform.w) / 2;
  transform.y = pos_y = (screen_height - transform.h) / 2;
}

player::Movement::Movement(): max_time_s(0.6), keypress_time_s(0.0) {}

void player::Movement::CountInertiaRatio(Graphics& graphics,
                                         MovementDirection passed_direction) {
  direction = passed_direction;

  switch (direction) {
  case kLeft:
    if ((keypress_time_s - graphics.delta_time_s) >= -max_time_s) {
      keypress_time_s -= graphics.delta_time_s;
    }
    break;

  case kRight:
    if ((keypress_time_s + graphics.delta_time_s) <= max_time_s) {
      keypress_time_s += graphics.delta_time_s;
    }
    break;

  case kUp:
    if ((keypress_time_s - graphics.delta_time_s) >= -max_time_s) {
      keypress_time_s -= graphics.delta_time_s;
    }
    break;

  case kDown:
    if ((keypress_time_s + graphics.delta_time_s) <= max_time_s) {
      keypress_time_s += graphics.delta_time_s;
    }
  }
}

void player::Movement::Move(Graphics& graphics, Player& Ufo) {
  double vector_length = std::sqrt(std::pow(Ufo.horizontal_speed, 2.0)
                         + std::pow(Ufo.vertical_speed, 2.0)) / Ufo.max_speed;

  switch (direction) {
  case kLeft:
  case kRight:
    Ufo.horizontal_speed = Ufo.max_speed * (keypress_time_s / max_time_s);
    Ufo.horizontal_step  = Ufo.horizontal_speed * graphics.delta_time_s
                           * graphics.pixelart_px_sz;
    break;

  case kUp:
  case kDown:
    Ufo.vertical_speed = Ufo.max_speed * (keypress_time_s / max_time_s);
    Ufo.vertical_step  = Ufo.vertical_speed * graphics.delta_time_s
                         * graphics.pixelart_px_sz;
  }

  // Prevents diagonal speed-ups.
  if ((Ufo.directions_number == 2) && (vector_length > 1.0)) {
    Ufo.horizontal_step /= vector_length;
    Ufo.vertical_step   /= vector_length;
  }
  switch (direction) {
  case kLeft:
  case kRight:
    Ufo.pos_x += Ufo.horizontal_step;
    break;

  case kUp:
  case kDown:
    Ufo.pos_y += Ufo.vertical_step;
  }
}
