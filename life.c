/*
 * Game of Life main program
 * Author: Ankur Gupta
 * Email: agupta4@wpi.edu
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	printf("Game of Life\n");

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


	/* Save the command-line arguments.
		 Also need to check if print and/or pause arguments were entered,
		 and if so, what they were.
		 A switch statement might be handy here.
	*/
	rows = atoi(argv[1]); // Convert from character string to integer.
	columns = atoi(argv[2]);
	gens = atoi(argv[3]);
	inputFileName = argv[4];

	/* Here is how you would allocate an array to hold the grid.
	*/
	// gridA = make2Dchar(nrows, ncolumns);
	// You should check that it succeeded.


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
