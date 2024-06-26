#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#ifdef __APPLE__
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#define SDL2_SUCCESS 0

namespace error
{
    void show_box(const std::string);

    class Exception_box: public std::runtime_error
    {
    public:
        explicit Exception_box(const std::string&);
    };
}

#endif
