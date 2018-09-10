/**
 * Game of Life shared configuration settings
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

int ROWS;
int COLUMNS;
int GENS;
int DO_PRINT;
int DO_PAUSE;
char *INPUT_FILENAME;

int getUserOptions(int argc, char **argv) {
	if((argc < 5 || argc > 7)) {
		printf("Usage: \n");
		printf("	./life rows columns generations inputFile [print] [pause]\n");
		return -1;
	}

	ROWS = atoi(argv[1]);
	COLUMNS = atoi(argv[2]);
	GENS = atoi(argv[3]); 
	INPUT_FILENAME = argv[3];

	
}
