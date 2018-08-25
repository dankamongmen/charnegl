#include <iostream>
#include <libconfig.h++>
#include "libcharn/config.h"

// Ensure that the toplevel is, if anything, groups.
// Throws a libconfig::ParseException on error.
void CharnConfig::validateToplevel(){
	libconfig::Setting& root = config.lookup("");
	for(int z = 0 ; z < root.getLength() ; ++z){
		libconfig::Setting& s = root[z];
		if(s.getType() != libconfig::Setting::Type::TypeGroup){
			throw libconfig::ParseException(s.getSourceFile(),
				s.getSourceLine(), s.getName());
		}
		CharnConfigModule *ccm = modules[s.getName()];
		if(!ccm){
      std::cerr << "warning: unknown config toplevel " << s.getName() << std::endl;
      warnings = true;
		}else{
		  ccm->validateConfig(s);
    }
	}
}

// TODO ParseException can be inspected via a (library-static) getLine/getError
void CharnConfig::loadString(const std::string &s){
	config.readString(s);
	validateToplevel();
}

void CharnConfig::loadFile(const std::string &s){
	config.readFile(s.c_str());
}
