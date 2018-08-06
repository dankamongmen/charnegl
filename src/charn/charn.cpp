#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <basedir.h>

static void
usage(const char *name,int status){
	FILE *fp = status ? stderr : stdout;
	fprintf(fp, "usage: %s [ options ]\n",name);
	fprintf(fp, "options:\n");
	fprintf(fp, "\t-c/--config filename: specify configuration file\n");
	fprintf(fp, "\t-e/--error: don't exit on soft X errors\n");
	fprintf(fp, "\t-h/--help: display this help text\n");
	fprintf(fp, "\t-v/--verbose: increase verbosity\n");
	exit(status);
}

int main(int argc, char *argv[]){
	const struct option longopts [] = {
		{ "help",	0,	NULL,	'h',	},
		{ "verbose",	0,	NULL,	'v',	},
		{ "error",	0,	NULL,	'e',	},
		{ "config",	0,	NULL,	'c',	},
		{ NULL,		0,	NULL,	0,	}
	};
	int opt, longopt;
	int ErrorSoftfail = 0;
	int Verbose = 0;
	const char *ConfigFile = NULL;
	opterr = 0; // disallow getopt() diagnostic to stderr
	while((opt = getopt_long(argc, argv, ":c:hve", longopts, &longopt)) >= 0){
		switch(opt){
			case 'h':
				usage(argv[0], EXIT_SUCCESS);
				break;
			case 'v':
				Verbose = 1;
				break;
			case 'e':
				ErrorSoftfail = 1;
				printf("Disabling X error passthrough\n");
				break;
			case 'c':
				if(ConfigFile){
					fprintf(stderr, "can't provide -c twice\n");
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
			std::cerr << "couldn't initialize XDG handle\n";
			exit(EXIT_FAILURE);
		}
		const char *xdgdir = xdgConfigHome(&xdg);
		std::cout << "XDGConfigHome: " << xdgdir << std::endl;
		xdgWipeHandle(&xdg);
	}
	return EXIT_SUCCESS;
}
