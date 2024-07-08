#ifndef OS_ENV_H_
#define OS_ENV_H_

// As the C++ doesn't like concatinating char* + char* (#define is like that), macros are replaced with global variables but at least constants.

#ifdef __APPLE__
const std::string SEPARATOR = "/";

#else
#ifdef _WIN32
const std::string SEPARATOR = "\\";

#else
#ifdef __linux__
const std::string SEPARATOR = "/";

#else
#error Supported platforms: GNU/Linux, Windows and macOS.

#endif
#endif
#endif

#define RESOURCES_PATH "res"

#define TEXTURES_PATH RESOURCES_PATH + SEPARATOR + "textures" + SEPARATOR
#define HITBOXES_PATH RESOURCES_PATH + SEPARATOR + "hitboxes" + SEPARATOR
#define FONT_PATH     RESOURCES_PATH + SEPARATOR + "font" + SEPARATOR

#endif // OS_ENV_H_
