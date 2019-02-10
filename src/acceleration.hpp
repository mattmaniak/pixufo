#ifndef ACCELERATION_HPP
#define ACCELERATION_HPP

class Player;

class Player_acceleration
{
	public:
	const float max_time;
	float       elapsed_time;
	float       current_time;

	Player_acceleration(const float passed_max_time);

	void set_direction(Player* Ufo);
};

#endif
