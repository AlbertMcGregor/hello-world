#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "json/document.h"
#include "json/istreamwrapper.h"
#include <fstream>

class Settings
{
public:

	rapidjson::Document jsonsettings;

	void setConstants();

	static float
		PIPE_SPAWN_FREQUENCY,
		PIPE_GAP,
		UPPER_PIPE_SCREEN_THRESHOLD,
		LOWER_PIPE_SCREEN_THRESHOLD,
		PIPE_MOVEMENT_SPEED,
		BIRD_COLLISION_BITMASK,
		OBSTACLE_COLLISION_BITMASK,
		POINT_COLLISION_BITMASK,
		BIRD_FLYING_SPEED,
		BIRD_FALLING_SPEED,
		BIRD_FLY_DURATION,
		SCORE_FONT_SIZE,
		PIPE_SCALE;
};



#endif // __SETTINGS_H__
