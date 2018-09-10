/**
 * Game of Life main program
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

int main(int argc, char **argv) {
	printf("Game of Life\n");

	if(getUserOptions(argc, argv) == -1) {
		return EXIT_FAILURE;
	}

	char *inputFileName;
	FILE *input;

	int rows;
	int columns;
	int gens;
	int doPrint;
	int doPause;

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("	./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	rows = atoi(argv[1]); // Convert from character string to integer.
	columns = atoi(argv[2]);
	gens = atoi(argv[3]);
	inputFileName = argv[4];

	doPrint = argv[5][0] == 'y' ? 1 : 0;
	doPause = argv[5][0] == 'y' ? 1 : 0;

	/* Eventually, need to try to open the input file.
	*/
	input = fopen(inputFileName, "r");
	if (!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}


	/*Once opened, you can read from the file one character at a time with fgetc().
	 * You can read one line at a time using fgets().
	 * You can read from standard input (the keyboard) with getchar().
	*/

	return EXIT_SUCCESS;
}
