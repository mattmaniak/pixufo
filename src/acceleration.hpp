#ifndef ACCELERATION_HPP
#define ACCELERATION_HPP

class Player;

enum acceleration_direction
{
	acc_up,
	acc_down,
	acc_left,
	acc_right
};

class Player_acceleration
{
	public:
	acceleration_direction direction;

	bool        active;
	const float max_time;
	float       elapsed_time;
	float       current_time;

	Player_acceleration(const float passed_max_time);

	void  activate(acceleration_direction passed_direction);
	void  set_direction(Player* Ufo);
	float count_step_length(Player* Ufo);
};

#endif
