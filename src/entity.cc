// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "entity.h"

Entity::Entity(
    Graphics& graphics,
    std::string name,
    const double passed_speed,
    const Uint32 passed_single_frame_time_ms):
Sprite(
    graphics,
    name,
    passed_single_frame_time_ms) {
  std::random_device device;
  std::mt19937 random_generator(device());
  std::uniform_real_distribution<double>
  distribution(passed_speed / 2.0, passed_speed);

  if (!LoadHitbox(graphics)) {
    throw std::runtime_error("");
  }

  // Disable speed randomization for the Player.
  if (name == "ufo") {
    max_speed = passed_speed;
  } else {
    max_speed = distribution(random_generator);
  }
  hidden_timeout_ms = 0;
  step = 0.0;
}

bool Entity::LoadHitbox(Graphics& graphics) {
  const std::string path_to_file = HITBOXES_PATH + name;
  std::size_t       rects_number = 0;

  FILE* hitbox_parts_file = std::fopen(path_to_file.c_str(), "r");

  if (hitbox_parts_file == nullptr) {
    error::ShowBox("Can't load the hitbox file for: " + name);
    return false;
  }

  for (;;) {
    hitbox_parts.push_back({0, 0, 0, 0});

    std::fscanf(hitbox_parts_file, "(%d, %d) [%d, %d]\n",
                &hitbox_parts[rects_number].x, &hitbox_parts[rects_number].y,
                &hitbox_parts[rects_number].w, &hitbox_parts[rects_number].h);

    hitbox_parts[rects_number].w = hitbox_parts[rects_number].w
                                   * graphics.pixelart_px_sz;

    hitbox_parts[rects_number].h = hitbox_parts[rects_number].h
                                   * graphics.pixelart_px_sz;

    hitbox_parts[rects_number].x = hitbox_parts[rects_number].x
                                   * graphics.pixelart_px_sz;

    hitbox_parts[rects_number].y = hitbox_parts[rects_number].y
                                   * graphics.pixelart_px_sz;

    if (((hitbox_parts[rects_number].x    == 0)  // Empty file scenario.
         && (hitbox_parts[rects_number].y == 0)
         && (hitbox_parts[rects_number].w == 0)
         && (hitbox_parts[rects_number].h == 0))
        || (hitbox_parts[rects_number].x  < 0)   // Wrong position or/and size.
        || (hitbox_parts[rects_number].y  < 0)
        || (hitbox_parts[rects_number].w  < 1)
        || (hitbox_parts[rects_number].h  < 1)) {
      error::ShowBox("Wrong hitbox for the: " + name);
      return false;
    }
    if (std::feof(hitbox_parts_file)) {
      break;
    }
    rects_number++;

    if (rects_number > static_cast<std::size_t>(transform.w * transform.h)) {
      error::ShowBox("Too many hitbox parts for: " + name);
      std::fclose(hitbox_parts_file);

      return false;
    }
  }
  std::fclose(hitbox_parts_file);

  return true;
}

void Entity::RandomizeInitialPos() {
  std::mt19937 prng;
  prng.seed(std::random_device()());

  std::uniform_int_distribution<> distributor_x(max_x, 2 * max_x);
  std::uniform_int_distribution<> distributor_y(min_y, max_y);

  pos_x = distributor_x(prng);
  pos_y = distributor_y(prng);
}

bool Entity::Render(Graphics& graphics) {
// #ifdef DEBUG
//   SDL_Rect hbox_part;
// #endif

#ifndef DISABLE_RELATIVE_PLAYER_MOVEMENT
  if (name != "ufo") {
#endif
    transform.x = pos_x;
    transform.y = pos_y;
#ifndef DISABLE_RELATIVE_PLAYER_MOVEMENT
  }
#endif

  step = max_speed * graphics.delta_time_s * graphics.pixelart_px_sz;

  Animate(graphics);

  if (SDL_RenderCopy(graphics.Renderer, textures[current_frame_idx], nullptr,
                     &transform) != SDL2_SUCCESS) {
    error::ShowBox("Can't render the: " + name);
    return false;
  }

// #ifdef DEBUG
//   for (std::size_t idx = 0; idx < hitbox_parts.size(); idx++) {
//     hbox_part.w = hitbox_parts[idx].w;
//     hbox_part.h = hitbox_parts[idx].h;
//     hbox_part.x = pos_x + hitbox_parts[idx].x;
//     hbox_part.y = pos_y + hitbox_parts[idx].y;

//     if (SDL_SetRenderDrawColor(graphics.Renderer, 0, 255, 0, 100)
//         != SDL2_SUCCESS) {
//       error::ShowBox("Can't set color for: " + name + " hitbox.");
//       return false;
//     }
//     if (SDL_RenderFillRect(graphics.Renderer, &hbox_part) != SDL2_SUCCESS) {
//       error::ShowBox("Can't render the hitbox part for: " + name);
//       return false;
//     }
//   }
// #endif

  return true;
}
