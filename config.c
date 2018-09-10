/**
 * Game of Life shared configuration settings
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>

int ROWS;
int COLUMNS;
int GENS;
int DO_PRINT;
int DO_PAUSE;
char *INPUT_FILENAME;

int getUserOptions(int argc, char **argv) {
	if((argc < 5 || argc > 7)) {
		printf("Usage: \n");
		printf("	./life rows columns generations inputFile [print] [pause]\n");
		return -1;
	}

	ROWS = atoi(argv[1]);
	COLUMNS = atoi(argv[2]);
	GENS = atoi(argv[3]); 
	INPUT_FILENAME = argv[4];

	DO_PRINT = argv[5][0] == 'y' ? 1 : 0;
	DO_PAUSE = argv[6][0] == 'y' ? 1 : 0;

	return 0;
}

int** emptyBoard() {
	int **array = (int **) malloc(ROWS * sizeof(int *));
	if (!array) return (int **) NULL;

	for(int row = 0; row < ROWS; row++) {
		array[row] = malloc(COLUMNS * sizeof(int));
		if (!array[row]) return (int **) NULL;

		for(int col = 0; col < COLUMNS; col++) {
			array[row][col] = 0;
		}
	}

	return array;
}

int** boardFromFile(char *inputFileName) {
	FILE *input = fopen(inputFileName, "r");

	if(!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return (int**) NULL;
	}

	int **array = (int **) malloc(ROWS * sizeof(int *));
	if (!array) return (int **) NULL;

	for(int row = 0; row < ROWS; row++) {
		array[row] = malloc(COLUMNS * sizeof(int));
		if (!array[row]) return (int **) NULL;

		int valid = 1;
		char val;

		for(int item = 0; item < COLUMNS; item++) {
			if(valid) {
				val = fgetc(input);

				if(val == EOF || val == '\n' || val == '\0') {
					valid = 0;
					array[row][item] = 0;
				} else {
					array[row][item] = val == 'x' ? 1 : 0;
				}
			} else {
					array[row][item] = 0;
			}
		}

		while(valid && !(val == EOF || val == '\n' || val == '\0')) {
			val = fgetc(input);
		} 
	}
	

	fclose(input);
	
	printf("Printing the array:\n");

	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++) {
			printf("%d", array[i][j]);
		}
		printf("\n");
	}
	
	return array;
}
