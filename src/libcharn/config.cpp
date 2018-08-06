#include <libconfig.h++>
#include "libcharn/config.h"

void CharnConfig::loadString(const std::string &s){
	config.readString(s);
}
