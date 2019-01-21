#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "json\document.h"
class Settings
{
public:
	Settings();

	rapidjson::Document jsonsettings;
};

#endif // __SETTINGS_H__
