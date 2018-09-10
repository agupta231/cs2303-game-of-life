/**
 * Game of life generation logic and formatter.
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"

// Create symbolic constats defining what a row and column selector are. This is
// basically a fake enum
#define ROW 0
#define COLUMN 1

/**
 * @brief Print the internal game format into a pretty game of life state
 *
 * @param gameMap A game state. Must be a 2D binary int array
 */
void printMap(int **gameMap) {
  // Add some whitespace to make it look a bit more appealing
  printf("\n\n");

  /*
   * This loop traverses through the first set of arrays in the game map.
   *
   * Loop invariant: row will be the current row in the 2d array. Row is in the
   * range of [0, ROWS)
   */
  for(int row = 0; row < ROWS; row++) {
    /*
     * This loop traverses through each sub array in the 2d game map.
     *
     * Loop invariant: col will be the current colum in the 2d array. Col is in
     * the range of [0, COLS)
     */
    for(int col = 0; col < COLUMNS; col++) {
      // If the current square is occupied, then print out an 'x'
      if(gameMap[row][col]) {
        printf("x");
      } 
      // If the current squre is unoccupied, then print out a blank space 
      else {
        printf(" ");
      }
    }

    // Print out a new line because the row is over
    printf("\n");
  }
}

/**
 * @brief Helper function to determine if the proposed index is in the bounds
 * of the game board
 *
 * @param index the proposed index
 * @param selector the direction identitifer. Must be of symbolic constant ROWS
 * or COLUMNS
 *
 * @return 1 if the index is in the range, 0 otherwise
 */
int inRange(int index, int selector) {
  switch(selector) {
    // If user is proposing the index in the ROWS direction
    case ROW:
      return index >= 0 && index < ROWS;
    // If the user is proposing the index in the COLUMS direction
    case COLUMN:
      return index >= 0 && index < COLUMNS;
    // Something funky happens and the wrong selector type is passed through. In
    // this case print out an error message and return a 0.
    default:
      printf("Wrong selector type sent to inRange");
      return 0;
  }
}

/**
 * @brief Get the number of neighbors for a given state and position
 *
 * @param board the board to be get the neighbors from
 * @param row the row of the position
 * @param col the column of the position
 *
 * @return the number of neighbors.
 */
int getNeighbors(int** board, int row, int col) {
  // Base case: there are 0 neighbors
  int neighbors = 0;

  /*
   * Iterate through the horizontal translations when checking for neighbors.
   *
   * Loop invariant: i indicates which number is to be added to row so that the
   * corresponding neighbor can be checked.
   */
  for(int i = -1; i <= 1; i++) {
    /*
     * Iterate through the vertical translations when checking for neighbors.
     *
     * Loop invariant: j indicates which number is to be added to col so that 
     * the corresponding neighbor can be checked.
     */
    for(int j = -1; j<= 1; j++) {
      // If i and j are equal, that means that pos being checked is the
      // requesting square itself! Nobody wants that, so skip to the next
      // iteration.
      if(i == 0 && j == 0) {
        continue;
      }

      // First ensure that the proposed location is within the range of the
      // board to prevent seg faults
      if(inRange(row + i, ROW) && inRange(col + j, COLUMN)) {
        // Because the internal format of the game is 0 if it is unoccupied and
        // 1 if it is occupied, you just have to add the value in the square and
        // everything works out beautifully.
        neighbors += board[row + i][col + j];
      }
    }
  }

  return neighbors;
}

/**
 * @brief Compute the next generation in the game
 *
 * @param currentBoard the current generation
 * @param nextGen the 2d array that is going to hold the board for the next
 * generation
 */
void nextGeneration(int** currentBoard, int** nextGen) {
  /* 
   * Iterate through the rows in the board.
   *
   * Loop invariant: row will always be the current row that is being worked on
   * in the board
   */
  for(int row = 0; row < ROWS; row++) {
    /*
     * Iterate through the columns in the board.
     *
     * Loop invariant: col will always be the current column that is being
     * worked on in the board.
     */
    for(int col = 0; col < COLUMNS; col++) {
      // Store the current value that is being worked on in the board. Not
      // really necessary, but helps in keeping the codebase DRY.
      int value = currentBoard[row][col];

      // Calculate the number neighbors that the current squre has
      int neighbors = getNeighbors(currentBoard, row, col);

      // If the current square is occupied and it has 2-3 neighbors, then it
      // survives
      if(value == 1 && (neighbors == 2 || neighbors == 3)) {
        nextGen[row][col] = 1;
      }
      // If the current squre is occupied and has a different number of
      // neighbors, then it dies.
      else if (value == 1) {
        nextGen[row][col] = 0;
      }
      // If the current square is unoccupied and has exactly 3 neighbors, then a
      // new organism is born. The miracle of life!
      else if (value == 0 && neighbors == 3) {
        nextGen[row][col] = 1;
      }
      // Only other case that is left is if the squre is unoccupied with !=
      // neighbors, in which the squre remains unoccopied. Hello darkness, my
      // old friend...
      else {
        nextGen[row][col] = 0;
      }
    }
  }
}

/**
 * @brief Determine if two board states are equal
 *
 * @param A first board to check
 * @param B second board to check
 *
 * @return 1 if they are equal, 0 otherwise
 */
int isEqual(int** A, int** B) {
  // Initialize the number of differences to be 0
  int differences = 0;

  /* 
   * Iterate through the rows in the board.
   *
   * Loop invariant: row will always be the current row that is being worked on
   * in the board
   */
  for(int i = 0; i < ROWS; i++) {
    /*
     * Iterate through the columns in the board.
     *
     * Loop invariant: col will always be the current column that is being
     * worked on in the board.
     */
    for(int j = 0; j < COLUMNS; j++) {
      // If there is a mismatch in the same cell posititions, then increment
      // differences
      if(A[i][j] != B[i][j]) differences++;
    }
  }

  // Return 1 if there aren't any differences, and 0 otherwise
  return differences == 0;
}
