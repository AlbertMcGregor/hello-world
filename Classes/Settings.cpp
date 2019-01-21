#include "Settings.h"
#include "json/document.h"
#include "json/istreamwrapper.h"
#include <fstream>
#include <filesystem>
#include "json\filereadstream.h"

using namespace std;
using namespace rapidjson;

Settings::Settings()
{
	fstream ifs("properties/Settings.json");
	IStreamWrapper isw(ifs);
	jsonsettings.ParseStream(isw);
}






