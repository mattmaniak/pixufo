#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "model.hpp"

class Player: public Model
{
	public:
	const float max_levitation_time;
	float       current_levitation_time;

	Player(Rendering* Rendering, const std::string name,
	       const float passed_speed);
};

#endif
