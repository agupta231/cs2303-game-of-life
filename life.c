/**
 * Game of Life main program
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"

/**
 * @brief A helper function to parse the user input and determine if they would
 * like to see the next generation.
 *
 * @return 
 */
int userContinue() {
	printf("\nWould you like to see the next generation (y to cont.)? ");
	
	// Get the user's input
	char userIn = getchar();

	// If the user replies with 'y', then continue, else exit
	if(userIn == 'y') {
		return 1;
	} 

	// Exit the program becuase the user didn't want to continue
	exit(0);
}

/**
 * @brief Main function for the life program
 *
 * @param argc count of the arguments inputted from the cli
 * @param argv an arry of the arguments inputted from the cli
 *
 * @return 0 if successful run, 1 otherwise
 */
int main(int argc, char **argv) {
	// Print the title of the program
	printf("Game of Life\n");
	
	// Check if there was a problem reading the user inputs.
	if(getUserOptions(argc, argv) == -1) {
		return EXIT_FAILURE;
	}

	// Parse the input file and load it into board A
	int** A = boardFromFile(INPUT_FILENAME);

	// Ensure that there was no issue reading the input file
	if (A == NULL) {
		return EXIT_FAILURE;
	}

	// Create empty boards that will be used later to store the history of the
	// game
	int** B = emptyBoard();
	int** C = emptyBoard();


	// Because array pointers are constant, create a pointer to the array. That
	// way, you can swap the pointers instead of having to copy the contents of
	// the array.
	int*** p = &A;
	int*** q = &B;
	int*** spare = &C;

	// Print the first generation becuase it is always required.
	printf("Generation 0");
	printMap(A);

	/*
	 * Loop that handles the generation traversal in the program.
	 *
	 * Loop invariant: i is the current generation that is going on. The loop will
	 * continue until i reached the max generations (as defined by the user) or
	 * will leave early in case of a steady state / 2 state osciallation.
	 */
	for (int i = 1; i < GENS; i++) {
		// Compute the next generation of the game
		nextGeneration(*p, *q);

		// Temporarly store the address of pointer p (the previous generation).
		// NOTE: this variable doesn't need to be freed because it is just a pointer
		// that is allocated in the stack, and gets recreated on every loop.
		int*** temp = p;
		// Update p to be the newest generation
		p = q;
		// Update q to be 2 generations ago
		q = spare;
		// Update spare to be the previous generation
		spare = temp;

		// If the user speicified that they would like printed output
		if (DO_PRINT) {
			// If pause in enabled, and the user requested that the next generation be
			// outputted
			if (DO_PAUSE && userContinue()) {
					printf("Generation %d", i);
					printMap(*p);
			// If pause isn't enabled, then simply print the next generation
			} else if(!DO_PAUSE){
					printf("Generation %d", i);
					printMap(*p);
			}
		}

		// Check for a steady state or a 2-state osicallation. 
		//
		// Not gonna lie, not very proud of this one. This is a very naive
		// implementation of the program. A better solution would have been to
		// generate a hash for the state versus storing the whole state. That would
		// not only cut down on memory complexity, but time complexity as well.
		//
		// More details of this can be found in the README.
		if(isEqual(*p, *q) || isEqual(*p, *spare)) {
			// Give the user some input about why the program is terminating early and
			// exit
			printf("Osiallation Detected. Final State: ");
			printf("Generation %d", i);
			printMap(*p);

			return EXIT_SUCCESS;
		}

	}

	return EXIT_SUCCESS;
}
