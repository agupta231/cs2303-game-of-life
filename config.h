/**
 * config.h
 *
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#ifndef CONFIG_H_
#define CONFIG_H_

int ROWS;
int COLUMNS;
int GENS;
int DO_PRINT;
int DO_PAUSE;
char *INPUT_FILENAME;

// Function prototypes:
int getUserOptions(int argc, char **argv);
int** boardFromFile(char *inputFileName);
int** emptyBoard();

#endif
