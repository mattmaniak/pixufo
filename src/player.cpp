#include "player.hpp"

Player::Player(Rendering* Rendering, const std::string name,
               const float passed_speed):
Model(Rendering, name, passed_speed), max_levitation_time(3000.0f),
      current_levitation_time(0.0f)
{

}
