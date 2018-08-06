#include <cstdio>
#include <cstdlib>
#include <getopt.h>

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
		{ "help",       0,      NULL,	'h',	},
		{ "verbose",    0,      NULL,	'v',	},
		{ "error",      0,      NULL,	'e',	},
		{ "config",	0,	NULL,	'c',	},
		{ NULL,		0,      NULL,	0,	}
	};
	int opt, longopt;
	int ErrorSoftfail = 0;
	int Verbose = 0;
	while((opt = getopt_long(argc, argv, "hve", longopts, &longopt)) >= 0){
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
			default:
				usage(argv[0], EXIT_FAILURE);
				break;
		}
	}
	return EXIT_SUCCESS;
}
