#ifndef CHARN_SRC_LIB_CONFIGFILE
#define CHARN_SRC_LIB_CONFIGFILE

#include <libconfig.h++>

class ConfigFile {
public:
ConfigFile() : config() {};

// Load from the specified string.
// Propagates libconfig++ parsing exceptions.
void loadString(const std::string &s);

template<typename T> bool getValue(const std::string &s, T &val){
	return config.lookupValue(s, val);
}

private:
libconfig::Config config;
};

#endif
