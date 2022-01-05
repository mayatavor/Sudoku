#include <iostream>
#include <list>
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
}


/*
this function gets the row and the number to check, and checks is the number is in the row
input: row number, the number to check and the board
output: if the number is in the row or not
*/
bool CheckRow(int r, int num, Board b)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (b.board[r][i] == num)
			return true;
	}
}


/*
this function gets the column and the number to check, and checks is the number is in the column
input: column number, the number to check and the board
output: if the number is in the column or not
*/
bool CheckColumn(int c, int num, Board b)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (b.board[i][c] == num)
			return true;
	}
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
			break;
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (columns[j] == true)
				break;
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
		rows[i] = CheckRow(r, number, b);
	}
	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		columns[i] = CheckColumn(c, number, b);
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
			break;

		PlaceInfo place = FindPlaceToAddNumber(number, rowNum, columnNum, *b);

		if (place.columnNumber == 100)
			break;

		place.number = number;

		b->board[place.rowNumber][place.rowNumber] = place.number;
		columnNum += 3;
	}
}


bool Solve(Board b)
{

}


