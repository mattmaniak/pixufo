// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "graphics.h"

Graphics::Graphics():
    delta_time_s(0.0),
    Renderer_(nullptr),
    fps_(0),
    renderer_initialized_(false),
    window_initialized_(false),
    Window_(nullptr),
    frame_elapsed_time_ms_(0.0),
    fps_counter_(0) {
  const int default_driver = -1;

  if (!InitWindow()) {
    throw std::runtime_error("");
  }

  Renderer_ = SDL_CreateRenderer(Window_, default_driver,
                                SDL_RENDERER_ACCELERATED);

  if (Renderer_ == nullptr) {
    throw error::Exception_box("Can't create the Renderer.");
  }
  renderer_initialized_ = true;

#ifdef DEBUG
  if (SDL_SetRenderDrawBlendMode(Renderer_, SDL_BLENDMODE_BLEND)
      != SDL2_SUCCESS) {
    throw error::Exception_box("Can't enable the Renderer_ blend mode.");
  }
#endif

  if (SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't hide the mouse pointer.");
  }
  if (!GetPixelartPxSize()) {
    throw std::runtime_error("");
  }
}

Graphics::~Graphics() {
  if (renderer_initialized_) {
    SDL_DestroyRenderer(Renderer_);
    renderer_initialized_ = false;
  }
  if (window_initialized_) {
    SDL_DestroyWindow(Window_);
    window_initialized_ = false;
  }
}

bool Graphics::InitWindow() {
  const int         kUnusedSize = 0;
  const std::string kIconName   = "icon.bmp";
  SDL_Surface*      icon        = nullptr;

  if (SDL_GetDisplayBounds(CURRENT_DISPLAY_IDX, &Display_) != SDL2_SUCCESS) {
    error::ShowBox("Can't get the screen size at the initialization.");
    return false;
  }
  if ((Display_.w < MIN_DISPLAY_WIDTH) || (Display_.h < MIN_DISPLAY_HEIGHT)) {
    error::ShowBox("At least the HD screen resolution is required.");
    return false;
  }

  /* This function is returns nullptr on macOS when BMP files are not pulled
     correctly (via LFS). */
  Window_ = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, kUnusedSize, kUnusedSize,
                             SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (Window_ == nullptr) {
    error::ShowBox("Can't create the window.");
    return false;
  }
  window_initialized_ = true;

  icon = SDL_LoadBMP(kIconName.c_str());

  if (icon == nullptr) {
    return false;
  }
  SDL_SetWindowIcon(Window_, icon);
  SDL_FreeSurface(icon);

  return true;
}

bool Graphics::GetPixelartPxSize() {
  SDL_GetWindowSize(Window_, &Display_.w, &Display_.h);
  Display_.x = Display_.y = 0;

  if ((Display_.w > MAX_DISPLAY_WIDTH) || (Display_.h > MAX_DISPLAY_HEIGHT)) {
    error::ShowBox("Given display size is too big.");
    return false;
  }
  pixelart_px_size_ = Display_.w / PIXELART_DISPLAY_WIDTH;

  return true;
}

bool Graphics::SetUpNewFrame() {
  frame_start_time_ms_ = SDL_GetTicks();

  if (SDL_RenderClear(Renderer_) != SDL2_SUCCESS) {
    error::ShowBox("Can't clean the Renderer.");
    return false;
  }
  if (!GetPixelartPxSize()) {
    return false;
  }
  return true;
}

bool Graphics::CountFps() {
  fps_counter_++;

  if (fps_counter_ >= std::numeric_limits<Uint32>::max()) {
    error::ShowBox("Too many frames per second.");
    return false;
  }
  delta_time_s = (SDL_GetTicks() - frame_start_time_ms_) / 1000.0;
  frame_elapsed_time_ms_ += delta_time_s * 1000.0;

  if (frame_elapsed_time_ms_ >= 1000.0) {
    fps_ = fps_counter_;
    frame_elapsed_time_ms_ = 0.0;
    fps_counter_           = 0;

#ifdef DEBUG
    std::cout << fps_ << " FPS" << std::endl;
#endif
  }
  return true;
}
