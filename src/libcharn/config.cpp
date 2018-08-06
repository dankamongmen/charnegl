#include <libconfig.h++>
#include "libcharn/config.h"

void CharnConfig::loadString(const std::string &s){
	config.readString(s);
}

void CharnConfig::loadFile(const std::string &s){
	config.readFile(s.c_str());
}
