#include <fstream>
#include <gtest/gtest.h>
#include "libcharn/config.h"

#define CHARNCONFIG_EXTERNAL "../doc/charnrc"

TEST(CharnConfig, CharnConfigDefaultFile){
	CharnConfig cf;
	cf.loadFile(CHARNCONFIG_EXTERNAL); // FIXME accept as parameter somehow
}

TEST(CharnConfig, CharnConfigString){
	std::ifstream ifs(CHARNCONFIG_EXTERNAL);
	std::string str(std::istreambuf_iterator<char>{ifs}, {});
	// TODO load the file used in CharnConfigDefaultFile to our own string,
	// feed it in, use the same detailed checking
	CharnConfig cf;
	cf.loadString(str);
}
