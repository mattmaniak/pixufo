// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "game.h"

Game::Game(): state_(kMainMenu) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't initialize the SDL2.");
  }
  if (TTF_Init() != SDL2_SUCCESS) {
    throw error::Exception_box("Can't initialize the SDL2 ttf module.");
  }
  try {
    graphics_ = new Graphics;
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to initialize the Graphics module.");
  }

  try {
    level_ = new Level(*graphics_, "background_level", 2);
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to initialize the Level module.");
  }
}

Game::~Game() {
  delete graphics_;
  delete level_;

  TTF_Quit();
  SDL_Quit();  // 38 memleaks there.
}

State Game::get_state_() {
  return state_;
}

bool Game::RunCreditsMenuLoop() {
  Credits_menu current_menu(*graphics_);  // Unhandled exceptions possible.

  while (state_ == kCreditsMenu) {
    if (!graphics_->SetUpNewFrame()) {
      return false;
    }
    if (!current_menu.Render(*graphics_)) {
      return false;
    }
    if (!current_menu.SteerUsingKeyboard(state_)) {
      return false;
    }
    if (!graphics_->CountFps()) {
      return false;
    }
  }
  return true;
}

bool Game::RunLevelLoop() {
  // Has some artifacts in a background.
  const time_t kGameOverDurationMs = 2000;
  Font game_over_font(*graphics_, "Game Over", MAIN_FONT_SZ);

  while (state_ == kLevel) {
    if (!graphics_->SetUpNewFrame()) {
      return false;
    }
    if (!level_->player_->SteerUsingKeyboard(*graphics_, state_)) {
      return false;
    }
    level_->CheckEnemiesPosition(*graphics_);
    level_->CheckPlayerPos();

    if (level_->CheckPlayerCollision()) {
      // Additional frame to fully cover both models during a collision.
      if (!level_->Render(*graphics_)) {
        return false;
      }
      game_over_font.pos_x_ = (graphics_->Display_.w
                               - game_over_font.transform_.w) / 2;
      game_over_font.pos_y_ = (graphics_->Display_.h
                               - game_over_font.transform_.h) / 2;

      if (!game_over_font.Render(*graphics_)) {
        return false;
      }
      SDL_RenderPresent(graphics_->Renderer_);

      SDL_Delay(kGameOverDurationMs);  // Wait a moment after a player's death.
      state_ = kMainMenu;

      return true;
    }
    level_->score_points_ += graphics_->delta_time_s * 1000.0;

    if (level_->score_points_ >= std::numeric_limits<unsigned int>::max()) {
      error::ShowBox("You've reached the score limit.");
      return false;
    }
    if (!level_->Render(*graphics_)) {
      return false;
    }
    if (!graphics_->CountFps()) {
      return false;
    }
  }
  return true;
}

bool Game::RunMainMenuLoop() {
  Main_menu current_menu(*graphics_);  // Unhandled exceptions possible.

  while (state_ == kMainMenu) {
    if (!graphics_->SetUpNewFrame()) {
      return false;
    }
    if (!current_menu.Render(*graphics_)) {
      return false;
    }
    if (!current_menu.SteerUsingKeyboard(state_)) {
      return false;
    }
    if (!graphics_->CountFps()) {
      return false;
    }
  }
  level_->Reset();

  return true;
}

bool Game::RunPauseMenuLoop() {
  Pause_menu current_menu(*graphics_);  // Unhandled exceptions possible.

  while (state_ == kPauseMenu) {
    if (!graphics_->SetUpNewFrame()) {
      return false;
    }
    if (!current_menu.Render(*graphics_)) {
      return false;
    }
    if (!current_menu.SteerUsingKeyboard(state_)) {
      return false;
    }
    if (!graphics_->CountFps()) {
      return false;
    }
  }
  return true;
}
