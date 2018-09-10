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

	int** A = boardFromFile(INPUT_FILENAME);
	int** B = emptyBoard();
	int** C = emptyBoard();


	int*** p = &A;
	int*** q = &B;
	int*** spare = &C;

	printf("Generation 0");
	printMap(A);

	for (int i = 1; i < 10000; i++) {
		nextGeneration(*p, *q);

		printf("Generation %d", i);

		int*** temp = p;
		p = q;
		q = spare;
		spare = temp;

		printMap(*p);

		if(isEqual(*p, *q) || isEqual(*p, *spare)) {
			return EXIT_FAILURE;
		}

	}

	return EXIT_SUCCESS;
}
