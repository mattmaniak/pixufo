// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#include "graphics.h"

Graphics::Graphics():
    delta_time_s(0.0),
    Renderer(nullptr),
    fps(0),
    renderer_initialized(false),
    window_initialized(false),
    Window_(nullptr),
    frame_elapsed_time_ms_(0.0),
    fps_(0) {
  const int default_driver = -1;

  if (!InitWindow()) {
    throw std::runtime_error("");
  }

  Renderer = SDL_CreateRenderer(Window_, default_driver,
                                SDL_RENDERER_ACCELERATED);

  if (Renderer == nullptr) {
    throw error::Exception_box("Can't create the Renderer.");
  }
  renderer_initialized = true;

#ifdef DEBUG
  if (SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND)
      != SDL2_SUCCESS) {
    throw error::Exception_box("Can't enable the Renderer blend mode.");
  }
#endif

  if (SDL_SetRelativeMouseMode(SDL_TRUE) != SDL2_SUCCESS) {
    throw error::Exception_box("Can't hide the mouse pointer.");
  }
  if (!GetPixelArtPixelSize()) {
    throw std::runtime_error("");
  }
}

Graphics::~Graphics() {
  if (renderer_initialized) {
    SDL_DestroyRenderer(Renderer);
    renderer_initialized = false;
  }
  if (window_initialized) {
    SDL_DestroyWindow(Window_);
    window_initialized = false;
  }
}

bool Graphics::InitWindow() {
  const int         unused_sz = 0;
  SDL_Surface*      Icon      = nullptr;
  const std::string icon_name = "icon.bmp";

  if (SDL_GetDisplayBounds(CURRENT_DISPLAY_IDX, &Display) != SDL2_SUCCESS) {
    error::ShowBox("Can't get the screen size at the initialization.");
    return false;
  }
  if ((Display.w < MIN_DISPLAY_WIDTH) || (Display.h < MIN_DISPLAY_HEIGHT)) {
    error::ShowBox("At least the HD screen resolution is required.");
    return false;
  }

  /* This function is returns nullptr on macOS when BMP files are not pulled
     correctly (via LFS). */
  Window_ = SDL_CreateWindow("PixUfo", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, unused_sz, unused_sz,
                             SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (Window_ == nullptr) {
    error::ShowBox("Can't create the window.");
    return false;
  }
  window_initialized = true;

  Icon = SDL_LoadBMP(icon_name.c_str());

  if (Icon == nullptr) {
    return false;
  }
  SDL_SetWindowIcon(Window_, Icon);
  SDL_FreeSurface(Icon);

  return true;
}

bool Graphics::GetPixelArtPixelSize() {
  SDL_GetWindowSize(Window_, &Display.w, &Display.h);

  if ((Display.w > MAX_DISPLAY_WIDTH) || (Display.h > MAX_DISPLAY_HEIGHT)) {
    error::ShowBox("Given display size is too big.");
    return false;
  }
  pixelart_px_sz = Display.w / PIXELART_DISPLAY_WIDTH;

  return true;
}

bool Graphics::SetUpNewFrame() {
  frame_start_time_ms_ = SDL_GetTicks();

  if (SDL_RenderClear(Renderer) != SDL2_SUCCESS) {
    error::ShowBox("Can't clean the Renderer.");
    return false;
  }
  if (!GetPixelArtPixelSize()) {
    return false;
  }
  return true;
}

bool Graphics::CountFps() {
  fps_++;

  if (fps_ >= std::numeric_limits<Uint32>::max()) {
    error::ShowBox("Too many frames per second.");
    return false;
  }
  delta_time_s = (SDL_GetTicks() - frame_start_time_ms_) / 1000.0;
  frame_elapsed_time_ms_ += delta_time_s * 1000.0;

  if (frame_elapsed_time_ms_ >= 1000.0) {
    fps = fps_;
    frame_elapsed_time_ms_ = 0.0;
    fps_                   = 0;

#ifdef DEBUG
    std::cout << fps << " FPS" << std::endl;
#endif
  }
  return true;
}
