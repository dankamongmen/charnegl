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
	CharnConfig cf;
	cf.loadString(str);
}

#define CHARNSTANZA_LABEL "testcharnstanza"
#define CHARNSTANZA_KEY "testcharnkey"
#define CHARNSTANZA_VAL "testcharnval"

class TestModule : public CharnConfigModule {
public:
virtual void validateConfig(libconfig::Setting& setting) override {
	ASSERT_EQ(1, setting.getLength());
	libconfig::Setting& s = setting[0];
	ASSERT_EQ(libconfig::Setting::Type::TypeString, s.getType());
	EXPECT_STREQ(CHARNSTANZA_KEY, s.getName());
	std::string val = s;
	EXPECT_EQ(CHARNSTANZA_VAL, val);
}

static std::string getModuleName(){
	return CHARNSTANZA_LABEL;
}

static std::unique_ptr<CharnConfigModule> CreateMethod(){ return std::make_unique<TestModule>(); }
};

// Verify that we can register a CharnConfigModule and have it called back for
// a relevant configuration.
TEST(CharnConfig, CharnConfigModule){
	CharnConfig cf;
	// toplevel CHARNSTANZA_LABEL won't pass without our module being registered
	cf.loadString(CHARNSTANZA_LABEL " = { " CHARNSTANZA_KEY "=\"" CHARNSTANZA_VAL "\"; };");
}

// Verify that an unregistered toplevel stanza gets flagged.
TEST(CharnConfig, CharnConfigModuleWarnings){
	CharnConfig cf;
	cf.loadString("qux = { foo=\"bar\"; };");
	EXPECT_TRUE(cf.hasWarnings());
}
