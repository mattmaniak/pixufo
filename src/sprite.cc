// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "sprite.h"

Sprite::Sprite(
    Graphics& graphics,
    std::string passed_name,
    const Uint32 passed_single_frame_time_ms):
    name(passed_name),
    current_frame_idx_(0),
    current_frame_start_time_ms_(passed_single_frame_time_ms) {
  if (!LoadTextures(graphics)) {
    throw std::runtime_error("Unable to load textures for " + name);
  }

  /* As there is only the first texture size check, trying to load animation
     with various texture sizes may brake it's rendering. */
  if (SDL_QueryTexture(textures_[current_frame_idx_], nullptr, nullptr,
                       &transform_.w, &transform_.h) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't get the size of the texture: " + name);
  }
  pos_x_ = 0.0;
  pos_y_ = 0.0;

  transform_.w *= graphics.pixelart_px_size_;
  transform_.h *= graphics.pixelart_px_size_;
}

Sprite::~Sprite() {
  if (current_frame_start_time_ms_ == 0) {
    SDL_DestroyTexture(textures_[current_frame_start_time_ms_]);
  } else {
    for (std::size_t idx = 0; idx < FRAMES_NUMBER; idx++) {
      SDL_DestroyTexture(textures_[idx]);
    }
  }
}

void Sprite::Animate(Graphics& graphics) {
  if (current_frame_start_time_ms_ > 0) {
    current_frame_elapsed_time_ms_ += graphics.delta_time_s_ * 1000.0;

    if (current_frame_elapsed_time_ms_ >= current_frame_start_time_ms_) {
      current_frame_elapsed_time_ms_ = 0;
      current_frame_idx_++;
    }
    if (current_frame_idx_ >= FRAMES_NUMBER) {
      current_frame_idx_ = 0;
    }
  }
}

void Sprite::CenterOnDisplay(unsigned int screen_width,
                             unsigned int screen_height) {
  transform_.x = pos_x_ = (screen_width  - transform_.w) / 2;
  transform_.y = pos_y_ = (screen_height - transform_.h) / 2;
}

void Sprite::Move(Graphics& graphics, double offset_x, double offset_y) {
  pos_x_ += offset_x * graphics.delta_time_s_ * graphics.pixelart_px_size_;
  pos_y_ += offset_y * graphics.delta_time_s_ * graphics.pixelart_px_size_;
}

void Sprite::Shift(Graphics& graphics, double offset_x, double offset_y) {
  pos_x_ += offset_x * graphics.pixelart_px_size_;
  pos_y_ += offset_y * graphics.pixelart_px_size_;
}

bool Sprite::Render(Graphics& graphics) {
  Animate(graphics);

  transform_.x = pos_x_;
  transform_.y = pos_y_;

  if (SDL_RenderCopy(graphics.renderer_, textures_[current_frame_idx_], nullptr,
                     &transform_) != SDL2_SUCCESS) {
    error::ShowBox("Can't render the: " + name);
    return false;
  }
  return true;
}

bool Sprite::LoadTextures(Graphics& graphics) {
  SDL_Surface* Image;
  std::string  path;

  if (current_frame_start_time_ms_ == 0) {  // No animation.
    path = TEXTURES_PATH + name + IMAGE_EXTENSION;

    Image = SDL_LoadBMP(path.c_str());
    if (Image == nullptr) {
      return false;
    }
    textures_[current_frame_idx_] =
      SDL_CreateTextureFromSurface(graphics.renderer_, Image);

    if (textures_[current_frame_idx_] == nullptr) {
      error::ShowBox("Can't create the texture from the image: " + name);
      return false;
    }
    SDL_FreeSurface(Image);
  } else {  // Dir with animations.
    for (std::size_t idx = 0; idx < FRAMES_NUMBER; idx++) {
      path = TEXTURES_PATH + name + SEPARATOR + std::to_string(idx)
             + IMAGE_EXTENSION;

      Image = SDL_LoadBMP(path.c_str());
      if (Image == nullptr) {
        return false;
      }
      textures_[idx] = SDL_CreateTextureFromSurface(graphics.renderer_, Image);

      if (textures_[idx] == nullptr) {
        return false;
      }
      SDL_FreeSurface(Image);
    }
  }
  return true;
}
