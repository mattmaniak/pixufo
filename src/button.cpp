#include "button.hpp"

Button::Button(Graphics& Graphics, const std::string text,
               const int passed_sz, const unsigned int passed_idx):
Font(Graphics, text, passed_sz), idx(passed_idx)
{

}
