/**
 * Game of Life main program
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"

int main(int argc, char **argv) {
	printf("Game of Life\n");

	if(getUserOptions(argc, argv) == -1) {
		return EXIT_FAILURE;
	}

	int** board = boardFromFile(INPUT_FILENAME);
	int** empty = emptyBoard();

	int*** A = &empty;
	int*** B = &empty;
	int*** C = &board;


	printf("Generation 0");
	printMap(*C);

	for (int i = 1; i < 20; i++) {
		B = A;

		nextGeneration(*C, *A);

		int*** temp = B;
		B = C;
		C = A;
		A = temp;

		printf("Generation %d", i);
		printMap(*C);

		if(isEqual(*A, *B) || isEqual(*B, *C)) {
			return EXIT_FAILURE;
		}

	}

	return EXIT_SUCCESS;
}
