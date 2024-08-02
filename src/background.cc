// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "background.h"

Background::Background(Graphics& graphics, std::string name):
Sprite(graphics, name, 0) {}

bool Background::TileAndRender(Graphics& graphics) {
  // + 1 - extra one for scrolling.
  unsigned int tiles_x = (graphics.Display.w / transform.w) + 1;
  unsigned int tiles_y = (graphics.Display.h / transform.h) + 1;

  if ((tiles_x >= std::numeric_limits<unsigned int>::max())
      || (tiles_y >= std::numeric_limits<unsigned int>::max())) {
    error::ShowBox("Too many tiles in the background.");
    return false;
  }
  ScrollEndlessly();

  for (unsigned int y = 0; y <= tiles_y; y++) {  // Tiling.
    for (unsigned int x = 0; x <= tiles_x; x++) {
      transform.x = pos_x + (x * transform.w);
      transform.y = pos_y + (y * transform.h);

      if (SDL_RenderCopy(graphics.Renderer, textures[current_frame_idx],
                         nullptr, &transform) != SDL2_SUCCESS) {
        error::ShowBox("Can't render the: " + name
                        + " as the tile background.");

        return false;
      }
    }
  }
  return true;
}

void Background::ScrollEndlessly() {
  if (pos_x > 0.0) {                  // Background shifted right.
    pos_x -= transform.w;             // Move the background one tile left.
  } else if (pos_x < -transform.w) {  // Background shifted left.
    pos_x += transform.w;             // Move the background one tile right.
  }

  if (pos_y > 0.0) {                  // Background shifted down.
    pos_y -= transform.h;             // Move the background one tile up.
  } else if (pos_y < -transform.h) {  // Background shifted up.
    pos_y += transform.h;             // Move the background one tile down.
  }
}
