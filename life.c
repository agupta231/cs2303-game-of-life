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
 * @return 1 if the user wants to continue. Exit otherwise
 */
int userContinue() {
  // Declare the variable that is in charge of the user's input
  char userIn;

  /*
   * Loop in charge of looping over until the user inputs a valid answer.
   *
   * This is purposefully an infinite loop, and is designed for the program to
   * stop working until the user finally decides to comply with the program.
   *
   * Loop invariant: Everytime this loop runs, it means that the user has either
   *                 given an invalid input, or hasn't inputted anything yet. In
   *                 either case, the only way that this loop will stop is if
   *                 the user inputs in a valid character.
   */
  while(1) {
    // Ask the user if they would like to see the next generation
    printf("\nWould you like to see the next generation (y/n)? ");

    // Label the section of the code where the input is taken in, but the
    // prompt isn't printed again.
    //
    // YES. I KNOW THAT GOTO IS TO NEVER BE USED IN ANY SORT OF PRODUCTION OR
    // ANY REAL CODEBASE. However, when a character is inputted in std,
    // getchar() will also pick up the special ascii characters as well. A naive
    // implementation of this function then causes it to print out the prompt
    // twice, which is quite gross. 
    //
    // By skipping to this line of code, it effectively throws away the useless
    // character, and makes the user input look quite sexy while doing so.
    //
    // The only reason why I am using goto is because:
    // 1. This is already an infite loop, meaning the the stopping criterion are
    //    in the body of the loop, rather than the conditional block. Using goto
    //    would normally bypass the conditional block, but that is trivial in
    //    this case because there is nothing in there.
    // 2. This label is in perhaps the least important function in the whole
    //    program, and I feel a lot better using goto here than a place that
    //    does some "real heavy lifting"
    // 3. I don't plan on using goto for the rest of my life, and I want to be
    //    be able to say that I used it at least once unironically.
    prompt:
      // Get the user's input
      userIn = getchar();
      
      // If the input was a special character, that means that there were left
      // over characters from the previous input. Use goto to flush them out. 
      if(userIn == '\n' || userIn == '\0') {
        goto prompt;
      }

      // If the user replies with 'y', then continue.
      // If the user replies with 'n', then exit
      // Else prompt again
      if(userIn == 'y') {
        return 1;
      } else if(userIn == 'n') {
        exit(0);
      } else {
        printf("Wrong data type inputted. Please type in 'y' or 'n' %c", userIn);
      }
  }
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
