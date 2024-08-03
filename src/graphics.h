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
  double        pixelart_px_size_;
  SDL_Rect      Display_;   // Holds the screen size.
  SDL_Rect      Last_bg_transform_;
  SDL_Renderer* Renderer_;  // Rendering context.
  Uint32        fps_;

  Graphics();
  ~Graphics();

  bool SetUpNewFrame();  // Prepare the window to rendering.
  bool CountFps();       // End the frame and count frames.

 private:
  bool renderer_initialized_;
  bool window_initialized_;

  SDL_Window* Window_;
  Uint32      frame_start_time_ms_;    // Set at the beginning of the frame.
  Uint32      frame_elapsed_time_ms_;  // As above but at the end of it.
  Uint32      fps_counter_;

  bool InitWindow();
  bool GetPixelartPxSize();
};

#endif  // SRC_GRAPHICS_H_
