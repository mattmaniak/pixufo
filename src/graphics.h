// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

#include "error.h"
#include "os_env.h"

#define CURRENT_DISPLAY_IDX 0
#define PIXELART_DISPLAY_WIDTH 640.0f

#define MIN_DISPLAY_WIDTH  1280
#define MIN_DISPLAY_HEIGHT 720

#define MAX_DISPLAY_WIDTH  16384  // Same as in
#define MAX_DISPLAY_HEIGHT 16384  // the SDL2.

#define IMAGE_EXTENSION ".bmp"

class Graphics {
 public:
  double delta_time_s;  // Time to handle and render the single frame.

  // Describes how big is the pixelart's pixel. Depends on the screen width;
  double        pixelart_px_sz;
  SDL_Rect      Display;   // Holds the screen size.
  SDL_Rect      Last_bg_transform;
  SDL_Renderer* Renderer;  // Rendering context.

  Graphics();
  ~Graphics();

  bool set_up_new_frame();  // Prepare the window to rendering.
  bool count_fps();         // End the frame and count frames.

 private:
  bool renderer_initialized;
  bool window_initialized;

  SDL_Window* Window_;
  Uint32      frame_start_time_ms_;    // Set at the beginning of the frame.
  Uint32      frame_elapsed_time_ms_;  // As above but at the end of it.
  Uint32      fps_;

  bool init_window_();
  bool get_pixelart_px_sz_();
};

#endif  // SRC_GRAPHICS_H_
