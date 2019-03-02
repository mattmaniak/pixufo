#ifndef OS_HPP
#define OS_HPP

#ifdef _WIN32
const std::string SEPARATOR = "\\";

#else
#ifdef __linux__
const std::string SEPARATOR = "/";
#endif

#endif

#endif
