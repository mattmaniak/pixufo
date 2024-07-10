#include "./background.h"

Background::Background(Graphics& graphics, std::string name):
Sprite(graphics, name, 0) {}

bool Background::tile_and_render(Graphics& graphics) {
  // + 1 - extra one for scrolling.
  unsigned int tiles_x = (graphics.Display.w / geometry.w) + 1;
  unsigned int tiles_y = (graphics.Display.h / geometry.h) + 1;

  if ((tiles_x >= std::numeric_limits<unsigned int>::max()) || (tiles_y >= std::numeric_limits<unsigned int>::max())) {
    error::show_box("Too many tiles in the background.");
    return false;
  }
  _scroll_endlessly();

  for (unsigned int y = 0; y <= tiles_y; y++) { // Tiling.
    for (unsigned int x = 0; x <= tiles_x; x++) {
      geometry.x = pos_x + (x * geometry.w);
      geometry.y = pos_y + (y * geometry.h);

      if (SDL_RenderCopy(graphics.renderer, textures[current_frame_idx], nullptr, &geometry) != SDL2_SUCCESS) {
        error::show_box("Can't render the: " + name + " as the tile background.");
        return false;
      }
    }
  }
  return true;
}

void Background::_scroll_endlessly() {
  if (pos_x > 0.0) { // Background shifted right.
    pos_x -= geometry.w; // Move the background one tile left.
  } else if (pos_x < -geometry.w) { // Background shifted left.
    pos_x += geometry.w; // Move the background one tile right.
  }

  if (pos_y > 0.0) { // Background shifted down.
    pos_y -= geometry.h; // Move the background one tile up.
  } else if (pos_y < -geometry.h) { // Background shifted up.
    pos_y += geometry.h; // Move the background one tile down.
  }
}
