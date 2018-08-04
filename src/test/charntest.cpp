#include <gtest/gtest.h>
#include "libcharn/configfile.h"

TEST(ConfigFile, ConfigFileLoad){
	auto cf = ConfigFile("");
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
