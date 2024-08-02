// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "game.h"

Game::Game(): _state(kMainMenu) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't initialize the SDL2.");
  }
  if (TTF_Init() != SDL2_SUCCESS) {
    throw error::Exception_box("Can't initialize the SDL2 ttf module.");
  }
  try {
    _graphics = new Graphics;
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to initialize the Graphics module.");
  }

  try {
    _level    = new Level(*_graphics, "background_level", 2);
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to initialize the Level module.");
  }
}

Game::~Game() {
  delete _graphics;
  delete _level;

  TTF_Quit();
  SDL_Quit();  // 38 memleaks there.
}

State Game::get_state() {
  return _state;
}

bool Game::RunCreditsMenuLoop() {
  Credits_menu Current_menu(*_graphics);  // Unhandled exceptions possible.

  while (_state == kCreditsMenu) {
    if (!_graphics->SetUpNewFrame()) {
      return false;
    }
    if (!Current_menu.Render(*_graphics)) {
      return false;
    }
    if (!Current_menu.SteerUsingKeyboard(_state)) {
      return false;
    }
    if (!_graphics->CountFps()) {
      return false;
    }
  }
  return true;
}

bool Game::RunLevelLoop() {
  // Has some artifacts in a background.
  Font Game_over_font(*_graphics, "Game Over", MAIN_FONT_SZ);

  while (_state == kLevel) {
    if (!_graphics->SetUpNewFrame()) {
      return false;
    }
    if (!_level->Ufo->SteerUsingKeyboard(*_graphics, _state)) {
      return false;
    }
    _level->CheckEnemiesPosition(*_graphics);
    _level->CheckPlayerPos();

    if (_level->CheckPlayerCollision()) {
      // Additional frame to fully cover both models during a collision.
      if (!_level->Render(*_graphics)) {
        return false;
      }

      Game_over_font.pos_x = (_graphics->Display.w
                              - Game_over_font.transform.w) / 2;
      Game_over_font.pos_y = (_graphics->Display.h
                              - Game_over_font.transform.h) / 2;

      if (!Game_over_font.Render(*_graphics)) {
        return false;
      }
      SDL_RenderPresent(_graphics->Renderer);

      SDL_Delay(2000);  // Wait a moment after a player's death.
      _state = kMainMenu;

      return true;
    }
    _level->score_points += _graphics->delta_time_s * 1000.0;

    if (_level->score_points >= std::numeric_limits<unsigned int>::max()) {
      error::ShowBox("You've reached the score limit.");
      return false;
    }
    if (!_level->Render(*_graphics)) {
      return false;
    }
    if (!_graphics->CountFps()) {
      return false;
    }
  }
  return true;
}

bool Game::RunMainMenuLoop() {
  Main_menu Current_menu(*_graphics);  // Unhandled exceptions possible.

  while (_state == kMainMenu) {
    if (!_graphics->SetUpNewFrame()) {
      return false;
    }
    if (!Current_menu.Render(*_graphics)) {
      return false;
    }
    if (!Current_menu.SteerUsingKeyboard(_state)) {
      return false;
    }
    if (!_graphics->CountFps()) {
      return false;
    }
  }
  _level->Reset();

  return true;
}

bool Game::RunPauseMenuLoop() {
  Pause_menu Current_menu(*_graphics);  // Unhandled exceptions possible.

  while (_state == kPauseMenu) {
    if (!_graphics->SetUpNewFrame()) {
      return false;
    }
    if (!Current_menu.Render(*_graphics)) {
      return false;
    }
    if (!Current_menu.SteerUsingKeyboard(_state)) {
      return false;
    }
    if (!_graphics->CountFps()) {
      return false;
    }
  }
  return true;
}
