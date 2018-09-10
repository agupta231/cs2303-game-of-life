# CS2303 Project 2 - Game of Life

This is the code base for my second project for CS2303.

Author: Ankur Gupta

## Summary

This program is an implementation of James Conway's Game of Life. It is a
biological simulation and fun to just play around with.

## Execution Instructions.

To compile, simply run `make`. You should then have an executable called `life`.
To run the program, the syntax is 
`./life rows columns generations inputFile [print] [pause]`, where the
parameters are defined as per the following:

* `rows` - how long you want your playing board to be
* `columsn` - how wide you want your playing board to be
* `generations` - how many generations you want to simulate before it stops
  itself
* `inputFile` - file name of starting board
* `print` - [optional] Whether you want every generation to be printed out
* `pause` - [optional] Whether you want to be asked to continue to the next gen.

## Implementation Dreams

There are a couple places where this program implementation could have been
sexier. For starters, instead of saving 3 versions of the entire board, it would
have been nice to create a hash function for the board. That way, you only need
to fully traverse a board once and you would be able to compare any two boards
uniquely. Unfortunately, I cut time a bit close on this assignment, and
collision management in hash functions are a harsh reality.

Additionally, I often noticed myself constantly iterating through the entire
game board multiple times, with the only real change being the logic inside of
the loops. It would have been cool to use anonymous functions to keep the code
DRYer, but I don't really know how to do that in C. I'm definitely going to look
into it... but again, time was a constraint.

## Loop Invariants

### Life.c
#### 1st while loop in userContine()
Loop in charge of looping over until the user inputs a valid answer.

This is purposefully an infinite loop, and is designed for the program to
stop working until the user finally decides to comply with the program.

Loop invariant: Everytime this loop runs, it means that the user has either
                given an invalid input, or hasn't inputted anything yet. In
                either case, the only way that this loop will stop is if
                the user inputs in a valid character.

#### 1st for loop in main()
Loop that handles the generation traversal in the program.

Loop invariant: i is the current generation that is going on. The loop will
continue until i reached the max generations (as defined by the user) or
will leave early in case of a steady state / 2 state osciallation.

### Game.c
#### 1st for loop in printMap()
This loop traverses through the first set of arrays in the game map.

Loop invariant: row will be the current row in the 2d array. Row is in the
range of [0, ROWS)

#### 2nd for loop in printMap()
This loop traverses through each sub array in the 2d game map.

Loop invariant: col will be the current colum in the 2d array. Col is in
the range of [0, COLS)

#### 1st for loop in getNeighbors()
Iterate through the horizontal translations when checking for neighbors.

Loop invariant: i indicates which number is to be added to row so that the
corresponding neighbor can be checked.

#### 2nd for loop in getNeighbors()
Iterate through the vertical translations when checking for neighbors.

Loop invariant: j indicates which number is to be added to col so that 
the corresponding neighbor can be checked.

#### 1st for loop in nextGeneration()
Iterate through the rows in the board.

Loop invariant: row will always be the current row that is being worked on
in the board

#### 2nd for loop in nextGeneration()
Iterate through the columns in the board.

Loop invariant: col will always be the current column that is being
worked on in the board.

#### 1st for loop in isEqual()
Iterate through the rows in the board.

Loop invariant: row will always be the current row that is being worked on
in the board

#### 2nd for loop in isEqual()
Iterate through the columns in the board.

Loop invariant: col will always be the current column that is being
worked on in the board.

### Config.c
#### 1st for loop in emptyBoard()
Iterate through the rows of the grid.

Loop invariant: the row variable is always the current row that is being
worked on in the grid

#### 2nd for loop in emptyBoard()
iterate through the items in each row.

Loop Invariant: the col variable indicates which column of the board is
currently being worked on

#### 1st for loop in boardFromFile()
Loop in charge of iterating through the text file.

Loop invariant: x is always the next character in the file. The loop will
only break when x == EOF, or x runs out of characters to read


#### 2nd for loop in boardFromFile()
Add whitespace to teh top of the grid

Loop invariant: the row variable is always the current row that is being
worked on in the grid

#### 3rd for loop in boardFromFile()
Add whitepspace in the extra top rows of the grid

Loop invariant: the item indicates the x position of the current item
that is being filled with 0s

#### 4th for loop in boardFromFile()
Fill in the rest of the board with the data from the text file.

Loop invariant: The row variable indicates the current (non-padded) row
that is being filled from the text file

#### 5th for loop in boardFromFile()
Left pad the initial setup from the text file

Loop invariant: i indicates the column in which a 0 has to be added in
order for the starting formation to be centered

#### 6th for loop in boardFromFile()
Input in the values from the text box

Loop Invariant: item indicates the column in which an organism from the
starting formation occupies or not.

#### 1st while loop in boardFromFile()
If there are still valid characters, simply move the file pointer up
until a new line or EOF. This allows for the lines in the text file to be
longer than board that the user speicifed.

Loop Invariant: The val is a pointer to a character in the same line as
the previous loops. This val will continue to iterate through the line in
the file until it reaches a special character, indicating that it has
reached the end of the line or the file.
