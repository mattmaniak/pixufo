// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "level.h"

Level::Level(
    Graphics& graphics,
    std::string bg_name,
    unsigned int enemies_number):
Scene(graphics, bg_name),
    enemies_number_(enemies_number) {
  const double kSizeToDisplayWidthRatio = 1.0;

  width_  = graphics.Display_.w * kSizeToDisplayWidthRatio;
  height_ = graphics.Display_.h * kSizeToDisplayWidthRatio;

  try {
    player_ = new Player(graphics);
  } catch (std::runtime_error) {
    throw std::runtime_error("");
  }
  AdjustEntityBorders(graphics, *player_);

  // Set the player's default position.
  player_->CenterOnDisplay(width_, height_);

  RandimizeEnemiesNumber();

  // Create all enemies.
  for (std::size_t idx = 0; idx < enemies_number_; idx++) {
    try {
      RandimizeEnemyType(graphics);
    } catch (std::runtime_error) {
      throw std::runtime_error("");
    }
    AdjustEntityBorders(graphics, *enemies_[idx]);
  }
}

Level::~Level() {
  for (auto& enemy : enemies_) {
    delete enemy;
  }
  delete player_;
}

void Level::Reset() {
  player_->Movements["horizontal"]->keypress_time_s_ = 0.0;
  player_->Movements["vertical"]->keypress_time_s_   = 0.0;

#ifdef DISABLE_RELATIVE_PLAYER_MOVEMENT
  player_->CenterOnDisplay(width_, height_);
#endif

  for (auto& enemy : enemies_) {
    enemy->RandomizeInitialPos();
  }
  score_points_ = 0;
}

void Level::AdjustAllEntitiesBorders(Graphics& graphics) {
  width_  = graphics.Display_.w;
  height_ = graphics.Display_.h;

  for (auto& enemy : enemies_) {
    AdjustEntityBorders(graphics, *enemy);
  }
  AdjustEntityBorders(graphics, *player_);
}

void Level::CheckPlayerPos() {
  // If the model is out of the level, it will be moved to the mirrored place.

  if (player_->pos_x_ < player_->min_x_) {
    player_->pos_x_ = player_->max_x_;
  } else if (player_->pos_x_ > player_->max_x_) {
    player_->pos_x_ = player_->min_x_;
  } else if (player_->pos_y_ < player_->min_y_) {
    player_->pos_y_ = player_->max_y_;
  } else if (player_->pos_y_ > player_->max_y_) {
    player_->pos_y_ = player_->min_y_;
  }
}

bool Level::CheckPlayerCollision() {
  for (std::size_t en_idx = 0; en_idx < enemies_.size(); en_idx++) {
    if (SDL_HasIntersection(&player_->transform_,
                            &enemies_[en_idx]->transform_)) {
      if (CheckPlayerAdvancedCollision(en_idx)) {
        return true;
      }
    }
  }
  return false;
}

void Level::CheckEnemiesPosition(Graphics& graphics) {
  for (auto& enemy : enemies_) {
    if ((enemy->pos_x_ < enemy->min_x_) || (enemy->pos_x_ > enemy->max_x_)) {
      enemy->hidden_timeout_ms_ += graphics.delta_time_s * 1000.0;
    }
    if (enemy->hidden_timeout_ms_ > NEBULA_HIDDEN_TIMEOUT_MS) {
      enemy->hidden_timeout_ms_ = 0;

      enemy->RandomizeInitialPos();
      enemy->pos_x_ = graphics.Display_.w - graphics.pixelart_px_size_;
    }
  }
}

bool Level::Render(Graphics& graphics) {
#ifdef DEBUG
  Font Fpsfont_(graphics, std::to_string(graphics.fps_) + " FPS", TEXT_FONT_SZ);
#endif
  Font Scorefont_(graphics, std::to_string(score_points_), TEXT_FONT_SZ);

#ifdef DEBUG
  Fpsfont_.pos_x_ = graphics.Display_.w - Fpsfont_.transform_.w
                    - (PADDING / 2.0);
  Fpsfont_.pos_y_ = PADDING / 2.0;
#endif

  Scorefont_.pos_x_ = Scorefont_.pos_y_ = PADDING / 2.0;  // Left, upper corner.

  if (!bg_->TileAndRender(graphics)) {
    return false;
  }

#ifdef DISABLE_RELATIVE_PLAYER_MOVEMENT
  bg_->Move(graphics, BACKGROUND_ABSOLUTE_HORIZONTAL_SPEED, 0.0);
#else
  bg_->Move(graphics,
            -player_->horizontal_speed * BACKGROUND_TO_PLAYER_SPEED,
            -player_->vertical_speed * BACKGROUND_TO_PLAYER_SPEED);
#endif

  for (auto& enemy : enemies_) {
    if (!enemy->Render(graphics)) {
      return false;
    }
#ifdef DISABLE_RELATIVE_PLAYER_MOVEMENT
    enemy->Move(graphics, -enemy->max_speed_, 0.0);  // Moving to the left.
#else
    enemy->Move(graphics,
                 -player_->horizontal_speed - enemy->max_speed_,
                 -player_->vertical_speed);
#endif
  }
  if (!player_->Render(graphics)) {
    return false;
  }
#ifdef DEBUG
  if (!Fpsfont_.Render(graphics)) {
    return false;
  }
#endif
  if (!Scorefont_.Render(graphics)) {
    return false;
  }
  SDL_RenderPresent(graphics.Renderer_);

  return true;
}

void Level::AdjustEntityBorders(Graphics& graphics, Entity& Entity) {
  Entity.min_x_ = graphics.pixelart_px_size_ - Entity.transform_.w;
  Entity.min_y_ = graphics.pixelart_px_size_ - Entity.transform_.h;
  Entity.max_x_ = width_  - graphics.pixelart_px_size_;
  Entity.max_y_ = height_ - graphics.pixelart_px_size_;
}

void Level::RandimizeEnemiesNumber() {
  std::mt19937 prng;
  prng.seed(std::random_device()());

  std::uniform_int_distribution<std::mt19937::result_type>
  distributor_enemies(MIN_NEBULAS_NUMBER, MAX_NEBULAS_NUMBER);

  enemies_number_ = distributor_enemies(prng);
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
      enemies_.push_back(new Entity(graphics, "nebula_wasp", 160.0, 80));
      break;

    case 4:
    case 5:
    case 6:
      enemies_.push_back(new Entity(graphics, "nebula_medium", 120.0, 100));
      break;

    case 7:
    case 8:
      enemies_.push_back(new Entity(graphics, "nebula_big", 90.0, 160));
      break;

    case 9:
      enemies_.push_back(new Entity(graphics, "nebula_umbrella", 50.0, 200));
    }
  } catch (std::runtime_error) {
    throw std::runtime_error("");
  }
}

bool Level::CheckPlayerAdvancedCollision(std::size_t en_idx) {
  SDL_Rect player_hitbox_part;
  SDL_Rect enemy_hitbox_part;

  // Check the Player's hitbox part by enemies_' hitbox part.
  for (std::size_t pl_hb_idx = 0; pl_hb_idx < player_->hitbox_parts_.size();
      pl_hb_idx++) {
    // Position the Player's hitbox part.
    player_hitbox_part.w = player_->hitbox_parts_[pl_hb_idx].w;
    player_hitbox_part.h = player_->hitbox_parts_[pl_hb_idx].h;
    player_hitbox_part.x = player_->pos_x_
                           + (player_->hitbox_parts_[pl_hb_idx].x);
    player_hitbox_part.y = player_->pos_y_
                           + (player_->hitbox_parts_[pl_hb_idx].y);

    for (std::size_t en_hb_idx = 0;
         en_hb_idx < enemies_[en_idx]->hitbox_parts_.size(); en_hb_idx++) {
      // Position the enemy's hitbox part.
      enemy_hitbox_part.w = enemies_[en_idx]->hitbox_parts_[en_hb_idx].w;
      enemy_hitbox_part.h = enemies_[en_idx]->hitbox_parts_[en_hb_idx].h;

      enemy_hitbox_part.x =
        enemies_[en_idx]->pos_x_
        + (enemies_[en_idx]->hitbox_parts_[en_hb_idx].x);
      enemy_hitbox_part.y =
        enemies_[en_idx]->pos_y_
        + (enemies_[en_idx]->hitbox_parts_[en_hb_idx].y);

      if (SDL_HasIntersection(&player_hitbox_part, &enemy_hitbox_part)) {
        return true;  // Collision.
      }
    }
  }
  return false;
}

void Level::RandomizeEnemiesPosition() {  // Causes infinite loop...
  for (std::size_t idx = 0; idx < enemies_.size() - 1; idx++) {
    while ((enemies_[idx]->transform_.x == enemies_[idx + 1]->transform_.x)
           || (enemies_[idx]->transform_.y
               == enemies_[idx + 1]->transform_.y)) {
      enemies_[idx]->RandomizeInitialPos();
    }
  }
}
