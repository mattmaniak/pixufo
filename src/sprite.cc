// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "sprite.h"

Sprite::Sprite(
    Graphics& graphics,
    std::string passed_name,
    const Uint32 passed_single_frame_time_ms):
    name(passed_name),
    current_frame_idx(0),
    current_frame_start_time_ms_(passed_single_frame_time_ms) {
  if (!LoadTextures(graphics)) {
    throw std::runtime_error("");
  }

  /* As there is only the first texture size check, trying to load animation
     with various texture sizes may brake it's rendering. */
  if (SDL_QueryTexture(textures[current_frame_idx], nullptr, nullptr,
                       &transform.w, &transform.h) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't get the size of the texture: " + name);
  }
  pos_x = 0.0;
  pos_y = 0.0;

  transform.w *= graphics.pixelart_px_sz;
  transform.h *= graphics.pixelart_px_sz;
}

Sprite::~Sprite() {
  if (current_frame_start_time_ms_ == 0) {
    SDL_DestroyTexture(textures[current_frame_start_time_ms_]);
  } else {
    for (std::size_t idx = 0; idx < FRAMES_NUMBER; idx++) {
      SDL_DestroyTexture(textures[idx]);
    }
  }
}

void Sprite::Move(Graphics& graphics, double offset_x, double offset_y) {
  pos_x += offset_x * graphics.delta_time_s * graphics.pixelart_px_sz;
  pos_y += offset_y * graphics.delta_time_s * graphics.pixelart_px_sz;
}

void Sprite::Animate(Graphics& graphics) {
  if (current_frame_start_time_ms_ > 0) {
    current_frame_elapsed_time_ms_ += graphics.delta_time_s * 1000.0;

    if (current_frame_elapsed_time_ms_ >= current_frame_start_time_ms_) {
      current_frame_elapsed_time_ms_ = 0;
      current_frame_idx++;
    }
    if (current_frame_idx >= FRAMES_NUMBER) {
      current_frame_idx = 0;
    }
  }
}

bool Sprite::Render(Graphics& graphics) {
  Animate(graphics);

  transform.x = pos_x;
  transform.y = pos_y;

  if (SDL_RenderCopy(graphics.Renderer, textures[current_frame_idx], nullptr,
                     &transform) != SDL2_SUCCESS) {
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
    textures[current_frame_idx] =
      SDL_CreateTextureFromSurface(graphics.Renderer, Image);

    if (textures[current_frame_idx] == nullptr) {
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
      textures[idx] = SDL_CreateTextureFromSurface(graphics.Renderer, Image);

      if (textures[idx] == nullptr) {
        return false;
      }
      SDL_FreeSurface(Image);
    }
  }
  return true;
}
