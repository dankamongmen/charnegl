#ifndef CHARN_SRC_LIB_CONFIG
#define CHARN_SRC_LIB_CONFIG

#include <map>
#include <memory>
#include <libconfig.h++>

// Each libcharn element looking to be part of the config file can register
// itself as a CharnConfigModule, implementing this interface.
class CharnConfigModule {
public:
CharnConfigModule() = default;
virtual ~CharnConfigModule() = default;
// validateConfig will be passed the Setting object for its stanza
virtual void validateConfig(libconfig::Setting& setting) = 0;
};

class CharnConfig {
public:
CharnConfig() : warnings(false), config() {};

// Load from the specified string. Propagates libconfig++ parsing exceptions.
void loadString(const std::string& s);

// Load from the specified file. Propagates libconfig++ parsing/IO exceptions.
void loadFile(const std::string& s);

// TODO kill this off
template<typename T> bool getValue(const std::string& s, T& val){
	return config.lookupValue(s, val);
}

bool hasWarnings(){
  return warnings;
}

private:
libconfig::Config config;
std::map<std::string, CharnConfigModule *> modules;
void validateToplevel();
bool warnings;
};

#endif
