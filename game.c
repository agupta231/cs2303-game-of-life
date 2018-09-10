/**
 * Game of life generation logic and formatter.
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"

#define ROW 0
#define COLUMN 1

void printMap(int **gameMap) {
	printf("\n\n");

	for(int row = 0; row < ROWS; row++) {
		for(int col = 0; col < COLUMNS; col++) {
			if(gameMap[row][col]) {
				printf("x");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int inRange(int index, int selector) {
	switch(selector) {
		case ROW:
			return index > 0 && index < ROWS;
		case COLUMN:
			return index > 0 && index < COLUMNS;
		default:
			return 0;
	}
}

int getNeighbors(int** board, int row, int col) {
	int neighbors = 0;

	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <=1; j++) {
			if(i == 0 && j == 0) {
				continue;
			}

			if(inRange(row + i, ROW) && inRange(col + j, COLUMN)) {
				neighbors += board[row + i][col + j];
			}
		}
	}

	return neighbors;
}

void nextGeneration(int** currentBoard, int** nextGen) {
	// int **nextGen = (int **) malloc(ROWS * sizeof(int *));
	// if (!nextGen) return (int **) NULL;

	for(int row = 0; row < ROWS; row++) {
		// nextGen[row] = malloc(COLUMNS + sizeof(int));
		// if (!nextGen[row]) return (int **) NULL;

		for(int col = 0; col < COLUMNS; col++) {
			int value = currentBoard[row][col];
			int neighbors = getNeighbors(currentBoard, row, col);
			
			// printf("Row: %d Col: %d\n", row, col);

			if(value == 1 && (neighbors == 2 || neighbors == 3)) {
				nextGen[row][col] = 1;
			}
			else if (value == 1) {
				nextGen[row][col] = 0;
			}
			else if (value == 0 && neighbors == 3) {
				nextGen[row][col] = 1;
			}
			else {
				nextGen[row][col] = 0;
			}
		}
	}
}

int isEqual(int** A, int** B) {
	int differences = 0;

	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++) {
			if(A[i][j] != B[i][j]) differences++;
		}
	}

	return differences == 0;
}
