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

	boardFromFile(INPUT_FILENAME);

	return EXIT_SUCCESS;
}
