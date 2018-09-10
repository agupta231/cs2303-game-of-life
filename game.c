/**
 * Game of life generation logic and formatter.
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "game.h"

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
