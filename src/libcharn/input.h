#ifndef CHARN_SRC_LIB_INPUT
#define CHARN_SRC_LIB_INPUT

#include <libconfig.h++>
#include "libcharn/config.h"

class InputRouter : public CharnConfigModule,
			public RegisteredInFactory<InputRouter> {
public:
virtual void validateConfig(libconfig::Setting& setting) override {
	// TODO validate out setting, build up Input
	s_bRegistered;
}
static std::string getModuleName(){ return "input"; }
static std::unique_ptr<CharnConfigModule> CreateMethod(){ return std::make_unique<InputRouter>(); }
};

#endif
