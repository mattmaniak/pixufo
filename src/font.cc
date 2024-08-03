// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "font.h"

Font::Font(
    Graphics& Graphics,
    std::string passed_text,
    const unsigned int passed_size):
    size(passed_size * Graphics.pixelart_px_size_),
    name_(FONT_NAME),
    text_(passed_text) {
  const std::string path = FONT_PATH + SEPARATOR + name_;
  SDL_Surface*      surface;

  font_ = TTF_OpenFont(path.c_str(), size);

  if (font_ == nullptr) {
    throw error::Exception_box("Can't load the font: " + path);
  }
  color_.r = 120;
  color_.g = 244;
  color_.b = 004;

  // Blended - high quality, Solid - low quality.
  surface = TTF_RenderUTF8_Blended(font_, text_.c_str(), color_);

  if (surface == nullptr) {
    throw error::Exception_box("Can't create the surface from the font: "
                               + path);
  }
  TTF_CloseFont(font_);

  texture_ = SDL_CreateTextureFromSurface(Graphics.renderer_, surface);

  if (texture_ == nullptr) {
    throw error::Exception_box("Can't create the texture from the font: "
                               + path);
  }
  SDL_FreeSurface(surface);

  if (SDL_QueryTexture(texture_, nullptr, nullptr, &transform_.w, &transform_.h)
      != SDL2_SUCCESS) {
    throw error::Exception_box("Can't get the size of the texture: " + name_);
  }
}

Font::~Font() {
  SDL_DestroyTexture(texture_);
}

bool Font::Render(Graphics& Graphics) {
  transform_.x = pos_x_;
  transform_.y = pos_y_;

  if (SDL_RenderCopy(Graphics.renderer_, texture_, nullptr, &transform_)
      != SDL2_SUCCESS) {
    error::ShowBox("Can't copy the texture: " + name_ + " to the renderer.");
    return false;
  }
  return true;
}
