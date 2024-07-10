#include "./player.h"

Player::Player(Graphics& graphics): Entity(graphics, "ufo", 110.0, 0) {
  horizontal_speed  = 0.0;
  vertical_speed    = 0.0;
  horizontal_step   = 0.0;
  vertical_step     = 0.0;
  directions_amount = 0;

  Movements.insert(std::make_pair("horizontal", new player::Movement));
  Movements.insert(std::make_pair("vertical",   new player::Movement));
}

Player::~Player() {
  delete Movements["horizontal"];
  delete Movements["vertical"];

  Movements.clear();
}

bool Player::keyboard_steering(Graphics& graphics, State& state) {
  SDL_Event    Event;
  const Uint8* keys;

  keys = SDL_GetKeyboardState(nullptr);
  SDL_PollEvent(&Event);

  directions_amount = 0;

  switch (Event.type) {
    case SDL_QUIT:
    return false;
  }
  if (keys[SDL_SCANCODE_LEFT]) {
    Movements["horizontal"]->count_ratio(graphics, left);
  }
  if (keys[SDL_SCANCODE_RIGHT]) {
    Movements["horizontal"]->count_ratio(graphics, right);
  }
  if (keys[SDL_SCANCODE_UP]) {
    Movements["vertical"]->count_ratio(graphics, up);
  }
  if (keys[SDL_SCANCODE_DOWN]) {
    Movements["vertical"]->count_ratio(graphics, down);
  }
  if (keys[SDL_SCANCODE_ESCAPE]) {
    state = pause_menu;
  }

  if ((horizontal_speed != 0.0f) && (vertical_speed != 0.0f)) {
    directions_amount = 2;
  }
  Movements["horizontal"]->move(graphics, *this);
  Movements["vertical"]->move(graphics, *this);

  return true;
}

player::Movement::Movement(): max_time_s(0.6), keypress_time_s(0.0) {}

void player::Movement::count_ratio(Graphics& graphics, dir passed_direction) {
  direction = passed_direction;

  switch (direction) {
  case left:
    if ((keypress_time_s - graphics.delta_time_s) >= -max_time_s) {
      keypress_time_s -= graphics.delta_time_s;
    }
    break;

  case right:
    if ((keypress_time_s + graphics.delta_time_s) <= max_time_s) {
      keypress_time_s += graphics.delta_time_s;
    }
    break;

  case up:
    if ((keypress_time_s - graphics.delta_time_s) >= -max_time_s) {
      keypress_time_s -= graphics.delta_time_s;
    }
    break;

  case down:
    if ((keypress_time_s + graphics.delta_time_s) <= max_time_s) {
      keypress_time_s += graphics.delta_time_s;
    }
  }
}

void player::Movement::move(Graphics& graphics, Player& Ufo) {
  double vector_length =
    std::sqrt(std::pow(Ufo.horizontal_speed, 2.0)
    + std::pow(Ufo.vertical_speed, 2.0)) / Ufo.max_speed;

  switch (direction) {
  case left:
  case right:
    Ufo.horizontal_speed = Ufo.max_speed * (keypress_time_s / max_time_s);
    Ufo.horizontal_step  =
      Ufo.horizontal_speed * graphics.delta_time_s * graphics.pixelart_px_sz;
    break;

  case up:
  case down:
    Ufo.vertical_speed = Ufo.max_speed * (keypress_time_s / max_time_s);
    Ufo.vertical_step  =
      Ufo.vertical_speed * graphics.delta_time_s * graphics.pixelart_px_sz;
  }

  // Prevents diagonal speed-ups.
  if ((Ufo.directions_amount == 2) && (vector_length > 1.0)) {
    Ufo.horizontal_step /= vector_length;
    Ufo.vertical_step   /= vector_length;
  }
  switch (direction) {
  case left:
  case right:
    Ufo.pos_x += Ufo.horizontal_step;
    break;

  case up:
  case down:
    Ufo.pos_y += Ufo.vertical_step;
  }
}
