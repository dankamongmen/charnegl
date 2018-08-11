#include <gtest/gtest.h>
#include "libcharn/config.h"

TEST(CharnConfig, CharnConfigString){
	CharnConfig cf;
	cf.loadString("crap = \"argh\";");
	std::string s;
	ASSERT_TRUE(cf.getValue("crap", s));
	EXPECT_EQ(s, "argh");
	EXPECT_FALSE(cf.getValue("bah", s));
}
