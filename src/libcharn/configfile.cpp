#include <libconfig.h++>
#include "libcharn/configfile.h"

void ConfigFile::loadString(const std::string &s){
	config.readString(s);
}
