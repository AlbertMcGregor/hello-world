#include "Settings.h"

using namespace std;
using namespace rapidjson;

void Settings::setConstants()
{
	ifstream ifs("properties/Settings.json");
	IStreamWrapper isw(ifs);
	jsonsettings.ParseStream(isw);

	PIPE_SPAWN_FREQUENCY = jsonsettings["pipe_spawn_frequency"].GetFloat();
	PIPE_GAP = jsonsettings["pipe_gap"].GetFloat();
	UPPER_PIPE_SCREEN_THRESHOLD = jsonsettings["upper_pipe_screen_threshold"].GetFloat(); 
	LOWER_PIPE_SCREEN_THRESHOLD = jsonsettings["lower_pipe_screen_threshold"].GetFloat();
	PIPE_MOVEMENT_SPEED = jsonsettings["pipe_movement_speed"].GetFloat();
	BIRD_COLLISION_BITMASK = jsonsettings["bird_collision_bitmask"].GetFloat();
	OBSTACLE_COLLISION_BITMASK = jsonsettings["obstacle_collision_bitmask"].GetFloat();
	POINT_COLLISION_BITMASK = jsonsettings["point_collision_bitmask"].GetFloat();
	BIRD_FLYING_SPEED = jsonsettings["bird_flying_speed"].GetFloat();
	BIRD_FALLING_SPEED = jsonsettings["bird_falling_speed"].GetFloat();
	BIRD_FLY_DURATION = jsonsettings["bird_fly_duration"].GetFloat();
	SCORE_FONT_SIZE = jsonsettings["score_font_size"].GetFloat();
	PIPE_SCALE = jsonsettings["pipe_scale"].GetFloat();
}

float
Settings::PIPE_SPAWN_FREQUENCY,
Settings::PIPE_GAP,
Settings::UPPER_PIPE_SCREEN_THRESHOLD,
Settings::LOWER_PIPE_SCREEN_THRESHOLD,
Settings::PIPE_MOVEMENT_SPEED,
Settings::BIRD_COLLISION_BITMASK,
Settings::OBSTACLE_COLLISION_BITMASK,
Settings::POINT_COLLISION_BITMASK,
Settings::BIRD_FLYING_SPEED,
Settings::BIRD_FALLING_SPEED,
Settings::BIRD_FLY_DURATION,
Settings::SCORE_FONT_SIZE,
Settings::PIPE_SCALE;






