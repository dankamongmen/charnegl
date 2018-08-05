#ifndef CHARN_SRC_LIB_CONFIGFILE
#define CHARN_SRC_LIB_CONFIGFILE

#include <libconfig.h++>

class ConfigFile {
public:
	ConfigFile() : config() {};

	// Load from the specified string.
	// Propagates libconfig++ parsing exceptions.
	void loadString(const std::string &s);

private:
	libconfig::Config config;
};

#endif
