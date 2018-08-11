#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <basedir.h>
#include "libcharn/config.h"

#define CONFIGFILE "charnrc"

static void
usage(const char *name, int status){
	std::ostream &os = status ? std::cerr : std::cout;
	os << "usage: " << name << " [ options ]\n";
	os << "options:\n";
	os << "\t-c/--config filename: specify configuration file\n";
	os << "\t-h/--help: display this help text\n";
	os << "\t-v/--verbose: increase verbosity" << std::endl;
	exit(status);
}

int main(int argc, char *argv[]){
	const struct option longopts [] = {
		{ "help",	0,	NULL,	'h',	},
		{ "verbose",	0,	NULL,	'v',	},
		{ "config",	0,	NULL,	'c',	},
		{ NULL,		0,	NULL,	0,	}
	};
	int opt, longopt;
	int Verbose = 0;
	char *ConfigFile = NULL;
	opterr = 0; // disallow getopt() diagnostic to stderr
	while((opt = getopt_long(argc, argv, ":c:hve", longopts, &longopt)) >= 0){
		switch(opt){
			case 'h':
				usage(argv[0], EXIT_SUCCESS);
				break;
			case 'v':
				Verbose = 1;
				break;
			case 'c':
				if(ConfigFile){
					std::cerr << "can't provide -c twice" << std::endl;
					usage(argv[0], EXIT_FAILURE);
				}
				ConfigFile = optarg;
				break;
			default:
				usage(argv[0], EXIT_FAILURE);
				break;
		}
	}
	if(!ConfigFile){
		xdgHandle xdg;
		if(!xdgInitHandle(&xdg)){
			// FIXME fall back to $HOME/
			std::cerr << "couldn't initialize XDG handle" << std::endl;
			exit(EXIT_FAILURE);
		}
		const char *xdgdir = xdgConfigHome(&xdg);
		std::cout << "XDGConfigHome: " << xdgdir << std::endl;
		const size_t xdglen = strlen(xdgdir);
		ConfigFile = new char[xdglen + strlen(CONFIGFILE) + 2];
		strcpy(ConfigFile, xdgdir);
		ConfigFile[xdglen] = '/';
		strcpy(ConfigFile + xdglen + 1, CONFIGFILE);
		xdgWipeHandle(&xdg);
	}
	CharnConfig cconfig;
	std::cout << "loading config from " << ConfigFile << std::endl;
	cconfig.loadFile(ConfigFile);
	return EXIT_SUCCESS;
}
