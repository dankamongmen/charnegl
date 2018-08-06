#include <libconfig.h++>
#include "libcharn/configfile.h"

void ConfigFile::loadString(const std::string &s){
	config.readString(s);
}

template<typename T> bool ConfigFile::getValue(const std::string &s, T &val){
	return config.lookupValue(s, val);
}

template bool ConfigFile::getValue(const std::string &s, std::string &val);
