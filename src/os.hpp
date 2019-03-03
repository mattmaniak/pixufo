#ifndef OS_HPP
#define OS_HPP

/* As the C++ doesn't like concatinating char* + char* (#define is like that),
macros are replaced with global variables but at least constants. */

#ifdef _WIN32
const std::string SEPARATOR = "\\";

#else
#ifdef __linux__
const std::string SEPARATOR = "/";
#endif

#endif

#endif
