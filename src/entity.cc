#include "./entity.h"

Entity::Entity(Graphics& graphics, std::string name, const double passed_speed, const Uint32 passed_single_frame_time_ms):
Sprite(graphics, name, passed_single_frame_time_ms), max_speed(passed_speed) {
  if (!load_hitbox(graphics)) {
    throw std::runtime_error("");
  }
  step = 0.0;
  hidden_timeout_ms = 0;
}

bool Entity::load_hitbox(Graphics& graphics) {
  const std::string path_to_file = HITBOXES_PATH + name;
  std::size_t       rects_amount = 0;

  FILE* hitbox_parts_file = std::fopen(path_to_file.c_str(), "r");

  if (hitbox_parts_file == nullptr) {
    error::show_box("Can't load the hitbox file for: " + name);
    return false;
  }

  for (;;) {
    hitbox_parts.push_back({0, 0, 0, 0});

    std::fscanf(hitbox_parts_file, "(%d, %d) [%d, %d]\n",
          &hitbox_parts[rects_amount].x,
          &hitbox_parts[rects_amount].y,
          &hitbox_parts[rects_amount].w,
          &hitbox_parts[rects_amount].h);

    hitbox_parts[rects_amount].w = hitbox_parts[rects_amount].w * graphics.pixelart_px_sz;
    hitbox_parts[rects_amount].h = hitbox_parts[rects_amount].h * graphics.pixelart_px_sz;

    hitbox_parts[rects_amount].x = hitbox_parts[rects_amount].x * graphics.pixelart_px_sz;
    hitbox_parts[rects_amount].y = hitbox_parts[rects_amount].y * graphics.pixelart_px_sz;

    if (((hitbox_parts[rects_amount].x   == 0)  // Empty file scenario.
      && (hitbox_parts[rects_amount].y == 0)
      && (hitbox_parts[rects_amount].w == 0)
      && (hitbox_parts[rects_amount].h == 0))
      || (hitbox_parts[rects_amount].x  < 0)  // Wrong position or/and size.
      || (hitbox_parts[rects_amount].y  < 0)
      || (hitbox_parts[rects_amount].w  < 1)
      || (hitbox_parts[rects_amount].h  < 1)) {
      error::show_box("Wrong hitbox for the: " + name);
      return false;
    }
    if (std::feof(hitbox_parts_file)) {
      break;
    }
    rects_amount++;

    if (rects_amount > static_cast<std::size_t>(geometry.w * geometry.h)) {
      error::show_box("Too many hitbox parts for: " + name);
      std::fclose(hitbox_parts_file);

      return false;
    }
  }
  std::fclose(hitbox_parts_file);

  return true;
}

void Entity::randomize_initial_pos() {
  std::mt19937 prng;
  prng.seed(std::random_device()());

  std::uniform_int_distribution<> distributor_x(max_x, 2 * max_x);
  std::uniform_int_distribution<> distributor_y(min_y, max_y);

  pos_x = distributor_x(prng);
  pos_y = distributor_y(prng);
}

bool Entity::render(Graphics& graphics) {
#ifdef DEBUG
  SDL_Rect hbox_part;
#endif

  geometry.x = pos_x;
  geometry.y = pos_y;

  step = max_speed * graphics.delta_time_s * graphics.pixelart_px_sz;

  animate(graphics);

  if (SDL_RenderCopy(graphics.renderer, textures[current_frame_idx], nullptr, &geometry) != SDL2_SUCCESS) {
    error::show_box("Can't render the: " + name);
    return false;
  }

#ifdef DEBUG
  for (std::size_t idx = 0; idx < hitbox_parts.size(); idx++) {
    hbox_part.w = hitbox_parts[idx].w;
    hbox_part.h = hitbox_parts[idx].h;
    hbox_part.x = pos_x + hitbox_parts[idx].x;
    hbox_part.y = pos_y + hitbox_parts[idx].y;

    if (SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 100) != SDL2_SUCCESS) {
      error::show_box("Can't set color for: " + name + " hitbox.");
      return false;
    }
    if (SDL_RenderFillRect(graphics.renderer, &hbox_part) != SDL2_SUCCESS) {
      error::show_box("Can't render the hitbox part for: " + name);
      return false;
    }
  }
#endif

  return true;
}
