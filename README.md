# sudoku

Program for solving sudoku & Program for checking is a sudoku is solved correctly

## Solving Sudoku

My solving algorithm is a plan of checking lines and rows for a specific number:
* The code enters a loop that can only end once the sudoku is solved.
* In every loop, the code gets one of all the possible numbers in sudoku (1 - 9).
* The code looks for a place to add the number:
  - First it checks for the number in a row. If the number is already in the row, it marks the row as taken. Else, it marks it as free.
  - Secondly, it checks for the number in a column. If the number is already in the column, it marks the column as taken. Else, it marks it as free.
  - After looking for free rows and columns, the code crosscheck the free rows and columns to see if there is an empty place to enter the number.
  - After checking that there is no error ( the code found a place), the code enters the number to the place.
* After checking all the possible places for all the numbers, the code checks for any one open space in rows, columns and cubes. If there is only one place missing, it will add the missing number.
* Before doing another number round, the code checks if the sudoku is already solved. If so, it will print the solved sudoku. Else, it will move on to the next number.

In my code, I have a few examples for sudokus that my code can solve. For now, it can only solve easy sudokus.

## Checking If Sudoku Is Solved Correctly

 I build an algorithm that checks if the sudoku is solved in the right way. 
 * First of all, I started by checking that the board has every number 9 times.
 * After that, if all the numbers apear 9 times, I checked to see if all the rows and columns have all of the numbers ( every row has numbers 1 through 9 plus every column has numbers 1 through 9 ).
 * Finally, I checked to see if every cube has all of the numbers ( every cube has numbers 1 through 9 ).
If all conditions were true -> the sudoku is solved currectly. If not -> there is an error.

