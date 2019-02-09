#include "button.hpp"

Button::Button(Rendering* Rendering, const std::string name,
               const unsigned int passed_idx):
Model(Rendering, name, 0.0f), idx(passed_idx)
{

}
