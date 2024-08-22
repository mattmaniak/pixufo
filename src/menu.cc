// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "menu.h"
#include "level.h"

Menu::Menu(Graphics& graphics):
Scene(graphics, "background_primary_menu"),
    selected_button_idx_(0) {
  try {
    sprites_.insert(std::make_pair("title", new Sprite(graphics, "title", 0)));
    sprites_.insert(std::make_pair("selection_arrow",
                                   new Sprite(graphics, "meteor", 0)));
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to add sprites to a menu.");
  }
  contains_text_           = false;
  selection_arrow_focused_ = true;

  sprites_["title"]->CenterOnDisplay(graphics.display_.w, graphics.display_.h);
  sprites_["title"]->Shift(graphics, 0.0, -sprites_["title"]->transform_.h);
}

Menu::~Menu() {
  delete sprites_["selection_arrow"];
  delete sprites_["title"];

  sprites_.clear();
}

bool Menu::Render(Graphics& graphics) {
  if (!bg_->TileAndRender(graphics)) {
    return false;
  }
  if (!sprites_["title"]->Render(graphics)) {
    return false;
  }

  for (std::size_t idx = 0; idx < buttons_.size(); idx++) {
    buttons_[idx]->pos_x_ = PADDING;
    buttons_[idx]->pos_y_ = graphics.display_.h
                            - (buttons_[idx]->transform_.h * buttons_.size())
                            + (idx * buttons_[idx]->transform_.h) - PADDING;

    buttons_[idx]->transform_.x = buttons_[idx]->pos_x_;
    buttons_[idx]->transform_.y = buttons_[idx]->pos_y_;

    if (!buttons_[idx]->Render(graphics)) {
      return false;
    }
    if (idx == selected_button_idx_) {
      sprites_["selection_arrow"]->pos_x_ = buttons_[idx]->transform_.w
                                            + PADDING;
      sprites_["selection_arrow"]->pos_y_ = buttons_[idx]->transform_.y;
    }
  }
  if (selection_arrow_focused_) {
    if (!sprites_["selection_arrow"]->Render(graphics)) {
      return false;
    }
  }
  if (contains_text_) {
    for (auto& Line : text_lines_) {
      if (!Line->Render(graphics)) {
        return false;
      }
    }
  }
  SDL_RenderPresent(graphics.renderer_);

#ifndef DISABLE_MOVABLE_BACKGROUND
  bg_->Move(graphics, -5.0, -5.0);
#endif

  return true;
}

Main_menu::Main_menu(Graphics& graphics): Menu(graphics) {
  try {
    buttons_.push_back(new Font(graphics, "Play", MAIN_FONT_SZ));
    buttons_.push_back(new Font(graphics, "Credits", MAIN_FONT_SZ));
#ifdef _WIN32
    buttons_.push_back(new Font(graphics, "Exit", MAIN_FONT_SZ));
#else
    buttons_.push_back(new Font(graphics, "Quit", MAIN_FONT_SZ));
#endif
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to add buttons with fonts to main menu.");
  }
}

Main_menu::~Main_menu() {
  for (auto& Button : buttons_) {
    delete Button;
  }
}

bool Main_menu::SteerUsingKeyboard(State& state) {
  SDL_Event input_event;
  SDL_PollEvent(&input_event);

  switch (input_event.type) {
  case SDL_QUIT:
    return false;

  case SDL_KEYDOWN:
    switch (input_event.key.keysym.sym) {
    case SDLK_UP:
      if (selected_button_idx_ > 0) {
        selected_button_idx_--;
      }
      break;

    case SDLK_DOWN:
      if (selected_button_idx_ < (buttons_.size() - 1)) {
        selected_button_idx_++;
      }
      break;

    case SDLK_RETURN:
      switch (selected_button_idx_) {
      case 0:
        state = kLevel;
        break;

      case 1:
        state = kCreditsMenu;
        break;

      case 2:
        return false;
      }
    }
  }
  return true;
}

Pause_menu::Pause_menu(Graphics& graphics): Menu(graphics) {
  try {
    buttons_.push_back(new Font(graphics, "Continue", MAIN_FONT_SZ));
#ifdef _WIN32
    buttons_.push_back(new Font(graphics, "Exit to Main Menu", MAIN_FONT_SZ));
#else
    buttons_.push_back(new Font(graphics, "Quit to Main Menu", MAIN_FONT_SZ));
#endif
  } catch (std::runtime_error) {
    throw std::runtime_error("Unable to add buttons with fonts to pause menu.");
  }
}

Pause_menu::~Pause_menu() {
  for (auto& Button : buttons_) {
    delete Button;
  }
}

bool Pause_menu::SteerUsingKeyboard(State& state) {
  SDL_Event input_event;
  SDL_PollEvent(&input_event);

  switch (input_event.type) {
  case SDL_QUIT:
    return false;
  }
  switch (input_event.key.keysym.sym) {
  case SDLK_UP:
    if (selected_button_idx_ > 0) {
      selected_button_idx_--;
    }
    break;

  case SDLK_DOWN:
    if (selected_button_idx_ < (buttons_.size() - 1)) {
      selected_button_idx_++;
    }
    break;

    case SDLK_RETURN:
    switch (selected_button_idx_) {
    case 0:
      state = kLevel;
      break;

    case 1:
      state = kMainMenu;
    }
  }
  return true;
}

Credits_menu::Credits_menu(Graphics& graphics): Menu(graphics) {
  const double kTextLeading = 1.5;

  try {
    buttons_.push_back(new Font(graphics, "Return", MAIN_FONT_SZ));

    text_lines_.push_back(new Font(graphics, "Programming", TEXT_FONT_SZ));
    text_lines_.push_back(new Font(graphics, "mattmaniak", TEXT_FONT_SZ));
    text_lines_.push_back(new Font(graphics, "Graphics", TEXT_FONT_SZ));
    text_lines_.push_back(new Font(graphics, "Jakub \"QooBooS\" Mieszczak",
                                   TEXT_FONT_SZ));

    // Center the lines.
    for (std::size_t idx = 0; idx < text_lines_.size(); idx++) {
      text_lines_[idx]->pos_x_ = graphics.display_.w - PADDING
                                 - text_lines_[idx]->transform_.w;
      text_lines_[idx]->pos_y_ = PADDING;

      if (idx > 0) {
        text_lines_[idx]->pos_y_ =
          text_lines_[idx - 1]->pos_y_
          + (text_lines_[idx - 1]->size * kTextLeading);
      }
    }
    contains_text_ = true;
  }
  catch (std::runtime_error) {
    throw std::runtime_error(
      "Unable to add buttons with fonts to credits menu.");
  }
  selected_button_idx_     = 1;
  selection_arrow_focused_ = false;
}

Credits_menu::~Credits_menu() {
  for (auto& Button : buttons_) {
    delete Button;
  }
  for (auto& Line : text_lines_) {
    delete Line;
  }
  buttons_.clear();
  text_lines_.clear();
}

bool Credits_menu::SteerUsingKeyboard(State& state) {
  SDL_Event input_event;
  SDL_PollEvent(&input_event);

  switch (input_event.type) {
  case SDL_QUIT:
    return false;
  }

  switch (input_event.key.keysym.sym) {
  case SDLK_UP:
  case SDLK_DOWN:
    selected_button_idx_     = 0;
    selection_arrow_focused_ = true;
    break;

  case SDLK_RETURN:
    switch (selected_button_idx_) {
    case 0:
      state = kMainMenu;
    }
  }
  return true;
}
