#ifndef OS_HPP
#define OS_HPP

#ifdef _WIN32
#define SEPARATOR "\\"

#else
#ifdef __linux__
#define SEPARATOR "/"
#endif

#endif

#endif
