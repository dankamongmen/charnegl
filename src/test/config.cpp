#include <fstream>
#include <gtest/gtest.h>
#include "libcharn/config.h"

#define CHARNCONFIG_EXTERNAL "../doc/charnrc"

// Verify that the default config can be loaded+validated directly as a file.
TEST(CharnConfig, CharnConfigDefaultFile){
	CharnConfig cf;
	cf.loadFile(CHARNCONFIG_EXTERNAL); // FIXME accept as parameter somehow
}

// Verify that the default config can be loaded+validated as a string.
TEST(CharnConfig, CharnConfigString){
	std::ifstream ifs(CHARNCONFIG_EXTERNAL);
	std::string str(std::istreambuf_iterator<char>{ifs}, {});
	// TODO load the file used in CharnConfigDefaultFile to our own string,
	// feed it in, use the same detailed checking
	CharnConfig cf;
	cf.loadString(str);
}

#define CHARNSTANZA_LABEL "testcharnstanza"

class TestModule : public CharnConfigModule, public RegisteredInFactory<TestModule> {
public:
virtual void validateConfig(libconfig::Setting& setting) override {
        // TODO validate out setting, build up Input
        s_bRegistered;
}
static std::string getModuleName(){ return CHARNSTANZA_LABEL; }
static std::unique_ptr<CharnConfigModule> CreateMethod(){ return std::make_unique<TestModule>(); }
};

// Verify that we can register a CharnConfigModule and have it called back for
// a relevant configuration.
TEST(CharnConfig, CharnConfigModule){
	CharnConfig cf;
	// toplevel "test" won't pass without our module being registered
	cf.loadString(CHARNSTANZA_LABEL " = { intest=\"testvalue\"; };");
}

// Verify that an unregistered toplevel stanza gets rejected.
TEST(CharnConfig, CharnConfigModuleReject){
	CharnConfig cf;
	bool excepted = false;
	try{
		cf.loadString("crap = { intest=\"testvalue\"; };");
	}catch(libconfig::ParseException& pe){
		excepted = true;
	}
	EXPECT_TRUE(excepted);
}
