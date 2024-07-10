#include "./font.h"

Font::Font(Graphics& Graphics,
    std::string passed_text,
    const unsigned int passed_size):
    size(passed_size * Graphics.pixelart_px_sz),
    _name(FONTNAME),
    _text(passed_text) {
  const std::string path = FONT_PATH + SEPARATOR + _name;
  SDL_Surface*      Surface;

  _font = TTF_OpenFont(path.c_str(), size);

  if (_font == nullptr) {
    throw error::Exception_box("Can't load the font: " + path);
  }
  _color.r = 120;
  _color.g = 244;
  _color.b = 004;

  // Blended - high quality, Solid - low quality.
  Surface = TTF_RenderUTF8_Blended(_font, _text.c_str(), _color);

  if (Surface == nullptr) {
    throw error::Exception_box("Can't create the surface from the font: " + path);
  }
  TTF_CloseFont(_font);

  _texture = SDL_CreateTextureFromSurface(Graphics.renderer, Surface);

  if (_texture == nullptr) {
    throw error::Exception_box("Can't create the texture from the font: " + path);
  }
  SDL_FreeSurface(Surface);

  if (SDL_QueryTexture(_texture, nullptr, nullptr, &geometry.w, &geometry.h) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't get the size of the texture: " + _name);
  }
}

Font::~Font() {
  SDL_DestroyTexture(_texture);
}

bool Font::render(Graphics& Graphics) {
  geometry.x = pos_x;
  geometry.y = pos_y;

  if (SDL_RenderCopy(Graphics.renderer, _texture, nullptr, &geometry) != SDL2_SUCCESS) {
    error::show_box("Can't copy the texture: " + _name + " to the renderer.");
    return false;
  }
  return true;
}
