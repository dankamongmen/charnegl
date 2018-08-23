#ifndef CHARN_SRC_LIB_INPUT
#define CHARN_SRC_LIB_INPUT

#include <libconfig.h++>
#include "libcharn/config.h"

class InputRouterConfig : public CharnConfigModule {
public:
// TODO validate out setting, build up Input
virtual void validateConfig(libconfig::Setting& setting) override { }

static std::string getModuleName(){
	return "input";
}

static std::unique_ptr<CharnConfigModule> CreateMethod(){
	return std::make_unique<InputRouterConfig>();
}
};

#endif
