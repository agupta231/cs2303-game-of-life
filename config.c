/**
 * Game of Life shared configuration settings
 * @author: Ankur Gupta <agupta4@wpi.edu>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

	if(argc >= 6) {
		DO_PRINT = argv[5][0] == 'y' ? 1 : 0;
	} else {
		DO_PRINT = 0;
	}
	
	if(DO_PRINT && argc == 7) {
		DO_PAUSE = argv[6][0] == 'y' ? 1 : 0;
	} else {
		DO_PAUSE = 0;
	}

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


	FILE *inputMeta = fopen(inputFileName, "r");
	int fileLines = 0;
	int maxLineWidth = 0;

	int currentLineWidth = 0;
	for(char x = getc(inputMeta); x != EOF; x = getc(inputMeta)) {
		if(x == '\n') {
			fileLines++;
			if(currentLineWidth > maxLineWidth) {
				maxLineWidth = currentLineWidth;
			}

			currentLineWidth = 0;
			continue;
		}

		currentLineWidth++;
 	}

	int **array = (int **) malloc(ROWS * sizeof(int *));
	if (!array) return (int **) NULL;

	int topPadding;
	int leftPadding;

	if(fileLines >= ROWS) {
		topPadding = 0;
	} else {
		topPadding = (ROWS - fileLines) / 2;
	}

	if(maxLineWidth >= COLUMNS) {
		leftPadding = 0;
	} else {
		leftPadding = (COLUMNS - maxLineWidth) / 2;
	}

	for(int row = 0; row < topPadding; row++) {
		array[row] = malloc(COLUMNS * sizeof(int));
		if (!array[row]) return (int **) NULL;

		for(int item = 0; item < COLUMNS; item++) {
			array[row][item] = 0;
		}
	}

	for(int row = topPadding; row < ROWS; row++) {
		array[row] = malloc(COLUMNS * sizeof(int));
		if (!array[row]) return (int **) NULL;

		int valid = 1;
		char val;

		for(int i = 0; i < leftPadding; i++) {
			array[row][i] = 0;
		}

		for(int item = leftPadding; item < COLUMNS; item++) {
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
	return array;
}
