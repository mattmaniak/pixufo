#ifndef OS_ENV_H_
#define OS_ENV_H_

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

#define RESOURCES_PATH "res"

#define TEXTURES_PATH RESOURCES_PATH + std::string(SEPARATOR) + "textures" \
        + std::string(SEPARATOR)

#define HITBOXES_PATH RESOURCES_PATH + std::string(SEPARATOR) + "hitboxes" \
        + std::string(SEPARATOR)

#define FONT_PATH RESOURCES_PATH + std::string(SEPARATOR) + "font" \
        + std::string(SEPARATOR)

#endif  // OS_ENV_H_
