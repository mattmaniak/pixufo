#include "button.hpp"

Button::Button(Graphics& Graphics, const std::string name,
               const unsigned int passed_idx):
Model(Graphics, name, 0.0f, false), idx(passed_idx)
{

}
