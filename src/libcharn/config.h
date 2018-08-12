#ifndef CHARN_SRC_LIB_CONFIG
#define CHARN_SRC_LIB_CONFIG

#include <libconfig.h++>

class CharnConfig {
public:
CharnConfig() : config() {};

// Load from the specified string. Propagates libconfig++ parsing exceptions.
void loadString(const std::string& s);

// Load from the specified file. Propagates libconfig++ parsing/IO exceptions.
void loadFile(const std::string& s);

template<typename T> bool getValue(const std::string& s, T& val){
	return config.lookupValue(s, val);
}

private:
libconfig::Config config;
void validateToplevel();
};

#endif
