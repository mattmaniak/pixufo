// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "level.h"

Level::Level(
    Graphics& graphics,
    std::string bg_name,
    unsigned int enemies_number):
Scene(graphics, bg_name),
    _nebulas_number(enemies_number) {
  const double size_to_screen_width_ratio = 1.0;

  _width  = graphics.Display.w * size_to_screen_width_ratio;
  _height = graphics.Display.h * size_to_screen_width_ratio;

  try {
    Ufo = new Player(graphics);
  } catch (std::runtime_error) {
    throw std::runtime_error("");
  }
  AdjustEnemiesBorders(graphics, *Ufo);

  // Set the player's default position.
  Ufo->CenterOnDisplay(_width, _height);

  RandimizeEnemiesNumber();

  // Create all enemies.
  for (std::size_t idx = 0; idx < _nebulas_number; idx++) {
    try {
      RandimizeEnemyType(graphics);
    } catch (std::runtime_error) {
      throw std::runtime_error("");
    }
    AdjustEnemiesBorders(graphics, *_nebulas[idx]);
  }
}

Level::~Level() {
  for (auto& Nebula : _nebulas) {
    delete Nebula;
  }
  delete Ufo;
}

void Level::Reset() {
  Ufo->Movements["horizontal"]->keypress_time_s = 0.0;
  Ufo->Movements["vertical"]->keypress_time_s   = 0.0;

#ifdef DISABLE_RELATIVE_PLAYER_MOVEMENT
  Ufo->CenterOnDisplay(_width, _height);
#endif

  for (auto& Nebula : _nebulas) {
    Nebula->RandomizeInitialPos();
  }
  score_points = 0;
}

void Level::AdjustEnemyBorder(Graphics& graphics) {
  _width  = graphics.Display.w;
  _height = graphics.Display.h;

  for (auto& Nebula : _nebulas) {
    AdjustEnemiesBorders(graphics, *Nebula);
  }
  AdjustEnemiesBorders(graphics, *Ufo);
}

void Level::CheckPlayerPos() {
  // If the model is out of the level, it will be moved to the mirrored place.

  if (Ufo->pos_x < Ufo->min_x) {
    Ufo->pos_x = Ufo->max_x;
  } else if (Ufo->pos_x > Ufo->max_x) {
    Ufo->pos_x = Ufo->min_x;
  } else if (Ufo->pos_y < Ufo->min_y) {
    Ufo->pos_y = Ufo->max_y;
  } else if (Ufo->pos_y > Ufo->max_y) {
    Ufo->pos_y = Ufo->min_y;
  }
}

bool Level::CheckPlayerCollision() {
  for (std::size_t en_idx = 0; en_idx < _nebulas.size(); en_idx++) {
    if (SDL_HasIntersection(&Ufo->transform, &_nebulas[en_idx]->transform)) {
      if (CheckPlayerAdvancedCollision(en_idx)) {
        return true;
      }
    }
  }
  return false;
}

void Level::CheckEnemiesPosition(Graphics& graphics) {
  for (auto& Nebula : _nebulas) {
    if ((Nebula->pos_x < Nebula->min_x) || (Nebula->pos_x > Nebula->max_x)) {
      Nebula->hidden_timeout_ms += graphics.delta_time_s * 1000.0;
    }
    if (Nebula->hidden_timeout_ms > NEBULA_HIDDEN_TIMEOUT_MS) {
      Nebula->hidden_timeout_ms = 0;

      Nebula->RandomizeInitialPos();
      Nebula->pos_x = graphics.Display.w - graphics.pixelart_px_sz;
    }
  }
}

bool Level::Render(Graphics& graphics) {
#ifdef DEBUG
  Font Fps_font(graphics, std::to_string(graphics.fps) + " FPS", TEXT_FONT_SZ);
#endif
  Font Score_font(graphics, std::to_string(score_points), TEXT_FONT_SZ);

#ifdef DEBUG
  Fps_font.pos_x = graphics.Display.w - Fps_font.transform.w - (PADDING / 2.0);
  Fps_font.pos_y = PADDING / 2.0;
#endif

  Score_font.pos_x = Score_font.pos_y = PADDING / 2.0;  // Left, upper corner.

  if (!Bg->TileAndRender(graphics)) {
    return false;
  }

#ifdef DISABLE_RELATIVE_PLAYER_MOVEMENT
  Bg->Move(graphics, BACKGROUND_ABSOLUTE_HORIZONTAL_SPEED, 0.0);
#else
  Bg->Move(graphics,
           -Ufo->horizontal_speed * BACKGROUND_TO_PLAYER_SPEED,
           -Ufo->vertical_speed * BACKGROUND_TO_PLAYER_SPEED);
#endif

  for (auto& Nebula : _nebulas) {
    if (!Nebula->Render(graphics)) {
      return false;
    }
#ifdef DISABLE_RELATIVE_PLAYER_MOVEMENT
    Nebula->Move(graphics, -Nebula->max_speed, 0.0);  // Moving to the left.
#else
    Nebula->Move(graphics,
                 -Ufo->horizontal_speed - Nebula->max_speed,
                 -Ufo->vertical_speed);
#endif
  }
  if (!Ufo->Render(graphics)) {
    return false;
  }
#ifdef DEBUG
  if (!Fps_font.Render(graphics)) {
    return false;
  }
#endif
  if (!Score_font.Render(graphics)) {
    return false;
  }
  SDL_RenderPresent(graphics.Renderer);

  return true;
}

void Level::AdjustEnemiesBorders(Graphics& graphics, Entity& Entity) {
  Entity.min_x = graphics.pixelart_px_sz - Entity.transform.w;
  Entity.min_y = graphics.pixelart_px_sz - Entity.transform.h;
  Entity.max_x = _width  - graphics.pixelart_px_sz;
  Entity.max_y = _height - graphics.pixelart_px_sz;
}

void Level::RandimizeEnemiesNumber() {
  std::mt19937 prng;
  prng.seed(std::random_device()());

  std::uniform_int_distribution<std::mt19937::result_type>
  distributor_enemies(MIN_NEBULAS_NUMBER, MAX_NEBULAS_NUMBER);

  _nebulas_number = distributor_enemies(prng);
}

void Level::RandimizeEnemyType(Graphics& graphics) {
  const int enemies_type_pool = 10;

  std::mt19937 prng;
  prng.seed(std::random_device()());

  std::uniform_int_distribution<>
  distributor_enemy_type(0, enemies_type_pool - 1);

  try {
    switch (distributor_enemy_type(prng)) {
    case 0:
    case 1:
    case 2:
    case 3:
      _nebulas.push_back(new Entity(graphics, "nebula_wasp", 160.0, 80));
      break;

    case 4:
    case 5:
    case 6:
      _nebulas.push_back(new Entity(graphics, "nebula_medium", 120.0, 100));
      break;

    case 7:
    case 8:
      _nebulas.push_back(new Entity(graphics, "nebula_big", 90.0, 160));
      break;

    case 9:
      _nebulas.push_back(new Entity(graphics, "nebula_umbrella", 50.0, 200));
    }
  } catch (std::runtime_error) {
    throw std::runtime_error("");
  }
}

bool Level::CheckPlayerAdvancedCollision(std::size_t en_idx) {
  SDL_Rect Player_hbox_part;
  SDL_Rect Nebula_hbox_part;

  // Check the Player's hitbox part by _nebulas' hitbox part.
  for (std::size_t pl_hb_idx = 0; pl_hb_idx < Ufo->hitbox_parts.size();
      pl_hb_idx++) {
    // Position the Player's hitbox part.
    Player_hbox_part.w = Ufo->hitbox_parts[pl_hb_idx].w;
    Player_hbox_part.h = Ufo->hitbox_parts[pl_hb_idx].h;
    Player_hbox_part.x = Ufo->pos_x + (Ufo->hitbox_parts[pl_hb_idx].x);
    Player_hbox_part.y = Ufo->pos_y + (Ufo->hitbox_parts[pl_hb_idx].y);

    for (std::size_t en_hb_idx = 0;
         en_hb_idx < _nebulas[en_idx]->hitbox_parts.size(); en_hb_idx++) {
      // Position the Nebula's hitbox part.
      Nebula_hbox_part.w = _nebulas[en_idx]->hitbox_parts[en_hb_idx].w;
      Nebula_hbox_part.h = _nebulas[en_idx]->hitbox_parts[en_hb_idx].h;

      Nebula_hbox_part.x =
        _nebulas[en_idx]->pos_x
        + (_nebulas[en_idx]->hitbox_parts[en_hb_idx].x);
      Nebula_hbox_part.y =
        _nebulas[en_idx]->pos_y
        + (_nebulas[en_idx]->hitbox_parts[en_hb_idx].y);

      if (SDL_HasIntersection(&Player_hbox_part, &Nebula_hbox_part)) {
        return true;  // Collision.
      }
    }
  }
  return false;
}

void Level::RandomizeEnemiesPosition() {  // Causes infinite loop...
  for (std::size_t idx = 0; idx < _nebulas.size() - 1; idx++) {
    while ((_nebulas[idx]->transform.x == _nebulas[idx + 1]->transform.x)
           || (_nebulas[idx]->transform.y == _nebulas[idx + 1]->transform.y)) {
      _nebulas[idx]->RandomizeInitialPos();
    }
  }
}
