#include <gtest/gtest.h>
#include "libcharn/config.h"

TEST(CharnConfig, CharnConfigDefaultFile){
	CharnConfig cf;
	cf.loadFile("../doc/charnrc"); // FIXME accept as parameter somehow
	// TODO enumerate more things?
	// TODO check lots of crap?
}

TEST(CharnConfig, CharnConfigString){
	// TODO load the file used in CharnConfigDefaultFile to our own string,
	// feed it in, use the same detailed checking
	CharnConfig cf;
	cf.loadString("input = { crap = \"argh\"; };");
	std::string s;
	ASSERT_TRUE(cf.getValue("input.crap", s));
	EXPECT_EQ(s, "argh");
	EXPECT_FALSE(cf.getValue("bah", s));
}
