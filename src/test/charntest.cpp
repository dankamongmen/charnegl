#include <gtest/gtest.h>
#include "libcharn/configfile.h"

TEST(ConfigFile, ConfigFileLoad){
	ConfigFile cf;
	cf.loadString("crap = \"argh\";");
	std::string s;
	ASSERT_TRUE(cf.getValue("crap", s));
	EXPECT_EQ(s, "argh");
	EXPECT_FALSE(cf.getValue("bah", s));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
