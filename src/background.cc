// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "background.h"

Background::Background(Graphics& graphics, std::string name):
Sprite(graphics, name, 0) {}

bool Background::TileAndRender(Graphics& graphics) {
  // + 1 - extra one for scrolling.
  unsigned int tiles_x = (graphics.Display_.w / transform_.w) + 1;
  unsigned int tiles_y = (graphics.Display_.h / transform_.h) + 1;

  if ((tiles_x >= std::numeric_limits<unsigned int>::max())
      || (tiles_y >= std::numeric_limits<unsigned int>::max())) {
    error::ShowBox("Too many tiles in the background.");
    return false;
  }
  ScrollEndlessly();

  for (unsigned int y = 0; y <= tiles_y; y++) {  // Tiling.
    for (unsigned int x = 0; x <= tiles_x; x++) {
      transform_.x = pos_x_ + (x * transform_.w);
      transform_.y = pos_y_ + (y * transform_.h);

      if (SDL_RenderCopy(graphics.Renderer_, textures_[current_frame_idx_],
                         nullptr, &transform_) != SDL2_SUCCESS) {
        error::ShowBox("Can't render the: " + name
                        + " as the tile background.");

        return false;
      }
    }
  }
  return true;
}

void Background::ScrollEndlessly() {
  if (pos_x_ > 0.0) {                   // Background shifted right.
    pos_x_ -= transform_.w;             // Move the background one tile left.
  } else if (pos_x_ < -transform_.w) {  // Background shifted left.
    pos_x_ += transform_.w;             // Move the background one tile right.
  }

  if (pos_y_ > 0.0) {                   // Background shifted down.
    pos_y_ -= transform_.h;             // Move the background one tile up.
  } else if (pos_y_ < -transform_.h) {  // Background shifted up.
    pos_y_ += transform_.h;             // Move the background one tile down.
  }
}
