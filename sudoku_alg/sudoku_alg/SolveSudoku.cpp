#include <iostream>
#include <list>
#include <ctime>
#include <string>
#include "Board.h"
#include "Structs.h"
#include <vector>

#define BOARD_SIZE 9
#define CUBE_SIZE 3

/*
this function gets the row and column of the first place in the cube and the number to check, and checks is the number is in the cube
input: row number, column number, the number to check and the board
output: if the number is in the cube or not
*/
bool CheckCube(int r, int c, int num, Board b)
{
	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (b.board[r + i][c + j] == num)
				return true;
		}
	}
	return false;
}

/*
this function gets the numbers that exist in the cube, row or column 
the function will return 0 if there is more than one number missing
otherwise it will return the missing number
*/
int ReturnMissing(int exists[], int count)
{
	if (count < 8) // if the amont numbers that exist in the cube is less than 8 it means that there is more than 1 number missing
		return 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (exists[i] == 0)
			return i + 1;
	}
	return 0;
}


/*
this function will check what is the missing number in the cube, 
if there is more than 1 number missing, it will return 0
input: the row and column of the cube and the board
output: if only one number is missing -> the number (1->9)
		if there is more than 1 number missing -> 0
*/
int WhatIsMissingInCube(int r, int c, Board b)
{
	int numbers_exist[BOARD_SIZE] = { 0,0,0,0,0,0,0,0 };
	int numbers_count = 0;

	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (b.board[i][j] != 0)
			{
				numbers_count++;
				numbers_exist[b.board[i][j] - 1] = b.board[i][j];
			}
		}
	}

	return ReturnMissing(numbers_exist, numbers_count);
}

/*
this function will check what is the missing number in the row,
if there is more than 1 number missing, it will return 0
input: the row and the board
output: if only one number is missing -> the number (1->9)
		if there is more than 1 number missing -> 0
*/
int WhatIsMissingInRow(int r, Board b)
{
	int numbers_exist[BOARD_SIZE] = { 0,0,0,0,0,0,0,0 };
	int numbers_count = 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (b.board[r][i] != 0)
		{
			numbers_count++;
			numbers_exist[b.board[r][i] - 1] = b.board[r][i];
		}
	}

	return ReturnMissing(numbers_exist, numbers_count);
}

/*
this function will check what is the missing number in the column,
if there is more than 1 number missing, it will return 0
input: the column and the board
output: if only one number is missing -> the number (1->9)
		if there is more than 1 number missing -> 0
*/
int WhatIsMissingInColumn(int c, Board b)
{
	int numbers_exist[BOARD_SIZE] = { 0,0,0,0,0,0,0,0 };
	int numbers_count = 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (b.board[i][c] != 0)
		{
			numbers_count++;
			numbers_exist[b.board[i][c] - 1] = b.board[i][c];
		}
	}

	return ReturnMissing(numbers_exist, numbers_count);
}



/*
this function gets the vector of the PlaceInfo of where the number can be added
the function will filter the full places(the places that already have a number)
input: the vector of PlaceInfo and the board
output: if there is only 1 free place, it will sent this place
		else it will sent a PlaceInfo where the row and column numbers are 100 (not a valid place)
*/
PlaceInfo FindFreePlace(std::vector<PlaceInfo> places, Board b)
{
	std::vector<PlaceInfo> free_places;
	for (size_t i = 0; i < places.size(); i++)
	{
		if (b.board[places[i].rowNumber][places[i].columnNumber] == 0)
			free_places.push_back(PlaceInfo(places[i]));
	}

	if (free_places.size() == 1)
		return free_places[0];
	return PlaceInfo(100, 100);
}


/*
this function gets the rows and columns of the cube and searches for places to put the number in
input: a bool array for the rows and a bool array for the columns
output: a vector of places to put the number in
*/
std::vector<PlaceInfo> FindPlacesInCube(bool rows[], bool columns[], int rNum, int cNum)
{
	std::vector<PlaceInfo> places;

	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		if (rows[i] == true)
			continue;
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (columns[j] == true)
				continue;
			places.push_back(PlaceInfo(i, j));
		}
	}

	return places;
}


/*
this function will get a cube that does not have the number and will find the place to add the number
input: the number, the row and column of the cube and the board
output: a PlaceInfo for the place to add the number
		if there is more than one place, it will return a PlaceInfo with the number 0
*/
PlaceInfo FindPlaceToAddNumber(int number, int c, int r, Board b)
{
	bool rows[] = { false,false,false };
	bool columns[] = { false,false,false };

	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		rows[i] = b.CheckForRow(r, number);
	}
	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		columns[i] = b.CheckForColumn(c, number);
	}

	std::vector<PlaceInfo> places = FindPlacesInCube(rows, columns, r, c);
	return FindFreePlace(places, b);
}


/*
this function goes over the cubes and checks where the number can be added, and if it can, it adds it
input: the number and a pointer to the board
output: none
*/
void ForLoopForNumber(int number, Board *b)
{
	int rowNum = 0, columnNum = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (columnNum == 9)
		{
			rowNum += 3;
			columnNum = 0;
		}
		if (CheckCube(rowNum, columnNum, number, *b))
			continue;

		PlaceInfo place = FindPlaceToAddNumber(number, rowNum, columnNum, *b);

		if (place.columnNumber == 100)
			continue;

		place.number = number;

		b->AddNumber(PlaceInfo(place.number, place.rowNumber, place.columnNumber));
		columnNum += 3;
	}
}


/*
this function gets the row, number and board, and adds the number to the row
		***** this function only gets a row with one number missing *****

input: the row number, the number to add and a pointer to the board
output: none
*/
void AddToRow(int row, int num, Board* b)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (b->board[row][i] == 0)
		{
			b->AddNumber(PlaceInfo(num, row, i));
			break;
		}
	}
}
/*
this function gets the column, number and board, and adds the number to the column
		***** this function only gets a column with one number missing *****

input: the column number, the number to add and a pointer to the board
output: none
*/
void AddToColumn(int column, int num, Board* b)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (b->board[i][column] == 0)
		{
			b->AddNumber(PlaceInfo(num, i, column));
			break;
		}
	}
}
/*
this function gets the row and column of the column, number and board, and adds the number to the cube
		***** this function only gets a cube with one number missing *****

input: the row number, the column number, the number to add and a pointer to the board
output: none
*/
void AddToCube(int row, int col, int num, Board* b)
{
	for (size_t i = row; i < CUBE_SIZE; i++)
	{
		for (size_t j = col; j < CUBE_SIZE; j++)
		{
			if (b->board[i][j] == 0)
			{
				b->AddNumber(PlaceInfo(num, i, j));
				break;
			}
		}
	}
}



/*
this function goes over the cubes, rows and columns to see if there is only one number missing. if so, it adds it
input: a pointer to the board
output: none
*/
void RowsColumnsAndCubes(Board* b)
{
	int now = 0;

	//adding to the rows
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		now = WhatIsMissingInRow(i, *b);
		if (now == 0)
			continue;
		
		AddToRow(i, now, b);
	}

	//adding to the column
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		now = WhatIsMissingInColumn(i, *b);
		if (now == 0)
			continue;

		AddToColumn(i, now, b);
	}

	//adding to the cube
	for (size_t i = 0; i < CUBE_SIZE; i+=3)
	{
		for (size_t j = 0; j < CUBE_SIZE; j+=3)
		{
			now = WhatIsMissingInCube(i, j, *b);
			if (now == 0)
				continue;

			AddToCube(i, j, now, b);
		}
	}

}



/*
this function is the loop to solve the sudoku
input: a pointer to the board
output: none
*/
void Solve(Board *b)
{
	while (b->GetCount() < 81)
	{
		for (size_t i = 0; i < BOARD_SIZE; i++)
		{
			ForLoopForNumber(i, b);
		}
		RowsColumnsAndCubes(b);
	}
}


