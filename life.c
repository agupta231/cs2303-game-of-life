/**
 * Game of Life main program
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"

int userContinue() {
	printf("\nWould you like to see the next generation (y to cont.)? ");

	char userIn = getchar();
	if(userIn == 'y') {
		return 1;
	} 

	exit(0);
}

int main(int argc, char **argv) {
	printf("Game of Life\n");

	if(getUserOptions(argc, argv) == -1) {
		return EXIT_FAILURE;
	}

	int** A = boardFromFile(INPUT_FILENAME);

	if (A == NULL) {
		return 1;
	}

	int** B = emptyBoard();
	int** C = emptyBoard();


	int*** p = &A;
	int*** q = &B;
	int*** spare = &C;

	printf("Generation 0");
	printMap(A);

	for (int i = 1; i < GENS; i++) {
		nextGeneration(*p, *q);

		int*** temp = p;
		p = q;
		q = spare;
		spare = temp;

		if (DO_PRINT) {
			if (DO_PAUSE && userContinue()) {
					printf("Generation %d", i);
					printMap(*p);
			} else if(!DO_PAUSE){
					printf("Generation %d", i);
					printMap(*p);
			}
		}

		if(isEqual(*p, *q) || isEqual(*p, *spare)) {
			printf("Osiallation Detected. Final State: ");
			printf("Generation %d", i);
			printMap(*p);

			return EXIT_SUCCESS;
		}

	}

	return EXIT_SUCCESS;
}
