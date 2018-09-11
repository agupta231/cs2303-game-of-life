/**
 * Game of Life shared configuration settings
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Global variables for the whole program
int ROWS;
int COLUMNS;
int GENS;
int DO_PRINT;
int DO_PAUSE;
char *INPUT_FILENAME;


/**
 * @brief Get the user parameters fromthe commandline
 *
 * @param argc the number of arguments
 * @param argv an array of the arguments
 *
 * @return 0 if success, -1 if error
 */
int getUserOptions(int argc, char **argv) {
  // If the user inputs an invalid number of arguments
  if((argc < 5 || argc > 7)) {
    printf("Usage: \n");
    printf("  ./life rows columns generations inputFile [print] [pause]\n");
    return -1;
  }

  // set the basic variables
  ROWS = atoi(argv[1]);
  COLUMNS = atoi(argv[2]);
  GENS = atoi(argv[3]); 
  INPUT_FILENAME = argv[4];

  // If doPrint is inputted
  if(argc >= 6) {
    // Determine what the user inputtedj
    DO_PRINT = argv[5][0] == 'y' ? 1 : 0;
  } else {
    // Defaults to false
    DO_PRINT = 0;
  }
  
  // If doPrint is true and the user inputted a value for pause
  if(DO_PRINT && argc == 7) {
    // Determine what the user inputted
    DO_PAUSE = argv[6][0] == 'y' ? 1 : 0;
  } else {
    // Default to false
    DO_PAUSE = 0;
  }

  // Return a success
  return 0;
}

/**
 * @brief Create an empty board the same size as the user specified
 *
 * @return a 2d array of ints (all 0s)
 */
int** emptyBoard() {
  // Dyanmically create the base array
  int **array = (int **) malloc(ROWS * sizeof(int *));
  // Make sure there weren't any problems
  if (!array) return (int **) NULL;

  /*
   * Iterate through the rows of the grid.
   *
   * Loop invariant: the row variable is always the current row that is being
   * worked on in the grid
   */
  for(int row = 0; row < ROWS; row++) {
    // Create a new array for each row
    array[row] = malloc(COLUMNS * sizeof(int));
    // Make sure there weren't any issues with the creation of it
    if (!array[row]) return (int **) NULL;

    /*
     * iterate through the items in each row.
     *
     * Loop Invariant: the col variable indicates which column of the board is
     * currently being worked on
     */
    for(int col = 0; col < COLUMNS; col++) {
      // Initialize the board by filling it up with 0s
      array[row][col] = 0;
    }
  }

  // Return the array
  return array;
}

/**
 * @brief Create a board from a given file
 *
 * @param inputFileName the input file name
 *
 * @return a 2d array indicating indiciating the board state which the file
 * depicted.
 */
int** boardFromFile(char *inputFileName) {
  // Convert the file into a file handler
  FILE *input = fopen(inputFileName, "r");

  // In case there was an error opening the file, pop an error message and
  // return a NULL array.
  if(!input) {
    printf("Unable to open input file: %s\n", inputFileName);
    return (int**) NULL;
  }

  // Open another file handler. This is to determine the shape of the initial
  // board, so it can be centered later
  FILE *inputMeta = fopen(inputFileName, "r");
  // The number of lines in the text file
  int fileLines = 0;
  // The maximum line with in the text file
  int maxLineWidth = 0;

  // The line width of the current line
  int currentLineWidth = 0;
  /*
   * Loop in charge of iterating through the text file.
   *
   * Loop invariant: x is always the next character in the file. The loop will
   * only break when x == EOF, or x runs out of characters to read
   */
  for(char x = getc(inputMeta); x != EOF; x = getc(inputMeta)) {
    // If the current character is the newline
    if(x == '\n') {
      // Increment the number of lines in the file
      fileLines++;
      // If the file width is greater than the maxFile width, adjusted the
      // maxFileWidth to fix that right up
      if(currentLineWidth > maxLineWidth) {
        maxLineWidth = currentLineWidth;
      }

      // Reset the currentLineWidth variable
      currentLineWidth = 0;
      // Continue on with the next iteration without incrementing the
      // currentLineWidth variable
      continue;
    }

    // increment the currentLineWidth
    currentLineWidth++;
  }

  // If the last line was the longest line, adjust the maxLineWidth variable to
  // account for that error
  if(currentLineWidth > maxLineWidth) maxLineWidth = currentLineWidth;

  // Create the base array
  int **array = (int **) malloc(ROWS * sizeof(int *));
  if (!array) return (int **) NULL;

  // Declare the topPadding and leftPadding for the starting states defined in
  // the text file
  int topPadding;
  int leftPadding;

  // If the text file is bigger than the number of rows, then the padding is 0
  if(fileLines >= ROWS) {
    topPadding = 0;
  } 
  // Otherwise, take the diffference and divide it by two
  else {
    topPadding = (ROWS - fileLines) / 2;
  }

  // If the text file is longer than the number of columns, then the padding is
  // 0.
  if(maxLineWidth >= COLUMNS) {
    leftPadding = 0;
  } 
  // Otherwise, take the difference anad divide it by two
  else {
    leftPadding = (COLUMNS - maxLineWidth) / 2;
  }


  /*
   * Add whitespace to teh top of the grid
   *
   * Loop invariant: the row variable is always the current row that is being
   * worked on in the grid
   */
  for(int row = 0; row < topPadding; row++) {
    // Create a new array for each row
    array[row] = malloc(COLUMNS * sizeof(int));
    // Make sure there weren't any issues with the creation of it
    if (!array[row]) return (int **) NULL;

    /*
     * Add whitepspace in the extra top rows of the grid
     *
     * Loop invariant: the item indicates the x position of the current item
     * that is being filled with 0s
     */
    for(int item = 0; item < COLUMNS; item++) {
      array[row][item] = 0;
    }
  }

  /*
   * Fill in the rest of the board with the data from the text file.
   * 
   * Loop invariant: The row variable indicates the current (non-padded) row
   * that is being filled from the text file
   */
  for(int row = topPadding; row < ROWS; row++) {
    // Create a new array for each row
    array[row] = malloc(COLUMNS * sizeof(int));
    // Make sure there weren't any issues with the creation of it
    if (!array[row]) return (int **) NULL;

    // Initialize flags to help assist with the parsing a bit later on
    int valid = 1;
    char val;

    /*
     * Left pad the initial setup from the text file
     *
     * Loop invariant: i indicates the column in which a 0 has to be added in
     * order for the starting formation to be centered
     */
    for(int i = 0; i < leftPadding; i++) {
      array[row][i] = 0;
    }

    /*
     * Input in the values from the text box
     *
     * Loop Invariant: item indicates the column in which an organism from the
     * starting formation occupies or not.
     */
    for(int item = leftPadding; item < COLUMNS; item++) {
      // If the next file character is on the same line and is a valid
      // character.
      if(valid) {
        // Read the next character from the file
        val = fgetc(input);

        // If the character is a stopping character, set valid to false so that
        // the loop skips over and fills the rest of the line with 0s. This
        // allows for the text in the file to be shorter than the desired
        // playing field.
        if(val == EOF || val == '\n' || val == '\0') {
          valid = 0;
          array[row][item] = 0;
        } 
        // Otherwise, set the current cell to what is defined in the file
        else {
          array[row][item] = val == 'x' ? 1 : 0;
        }
      } 
      // If the input is known to be invalid, fill the box with a 0
      else {
          array[row][item] = 0;
      }
    }

    // If there are still valid characters, simply move the file pointer up
    // until a new line or EOF. This allows for the lines in the text file to be
    // longer than board that the user speicifed.
    //
    // Loop Invariant: The val is a pointer to a character in the same line as
    // the previous loops. This val will continue to iterate through the line in
    // the file until it reaches a special character, indicating that it has
    // reached the end of the line or the file.
    while(valid && !(val == EOF || val == '\n' || val == '\0')) {
      val = fgetc(input);
    } 
  }
  
  // Close the file handlers
  fclose(input);
  fclose(inputMeta);
  
  // Return the game board
  return array;
}
