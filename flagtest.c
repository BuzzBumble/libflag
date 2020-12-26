#include "libflags.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	struct sf_flags *fs = sf_newFlags(5);
	//sf_addStrFlag(fs, "filename", "settings.csv", "Settings file for config");
	sf_addIntFlag(fs, "port", 1, "Port number for server");
	//sf_addBoolFlag(fs, "threaded", true, "if true, server will run on threads.");
	sf_printFlags(fs);

	printf("%d\n", fs->flags[0]->ftype);
	//printf("%d\n", ((struct sf_int *)fs->flags[0])->dval);
	
	sf_destroyFlags(fs);

	exit(0);
}
