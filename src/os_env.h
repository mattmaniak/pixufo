// Copyright 2018-2019, 2024 mattmaniak, Jakub "QooBooS" Mieszczak

#ifndef SRC_OS_ENV_H_
#define SRC_OS_ENV_H_

#include <string>

/* As the C++ doesn't like concatinating char* + char* (#define is like that),
   macros are replaced with global variables but at least constants. */

#if defined(__APPLE__) || defined(__linux__)
const char SEPARATOR[] = "/";

#else
#ifdef _WIN32
const char SEPARATOR[] = "\\";

#else
#error Supported platforms: GNU/Linux, Windows and macOS.

#endif
#endif

#if defined(__APPLE__) && defined(MACOS_BUNDLE)
/* An absolute working directory path is required for Bundle to read files from
   various locations in the Bundle itself.
   https://wiki.libsdl.org/SDL2/README/macos#working-directory */
#define RESOURCES_PATH SDL_GetBasePath() + std::string(SEPARATOR) + "res"
#else
#define RESOURCES_PATH "res"
#endif

#define TEXTURES_PATH RESOURCES_PATH + std::string(SEPARATOR) + "textures" \
        + std::string(SEPARATOR)

#define HITBOXES_PATH RESOURCES_PATH + std::string(SEPARATOR) + "hitboxes" \
        + std::string(SEPARATOR)

#define FONT_PATH RESOURCES_PATH + std::string(SEPARATOR) + "font" \
        + std::string(SEPARATOR)

#endif  // SRC_OS_ENV_H_
