#include <iostream>
#include <list>
#include <string>
#include "Board.h"
#include "Structs.h"

#define BOARD_SIZE 9


/*
this function gets the row and column of the first place in the cube and the number to check, and checks is the number is in the cube
input: row number, column number, the number to check and the board
output: if the number is in the cube or not
*/
bool CheckCube(int r, int c, int num, Board b)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
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

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
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
this function will get a cube that does not have the number and will find the place to add the number
input: the number, the row and column of the cube and the board
output: a PlaceInfo for the place to add the number
		if there is more than one place, it will return a PlaceInfo with the number 0
*/
PlaceInfo FindPlaceToAddNumber(int number, int c, int r, Board b)
{


}




/*
this function goes over the cubes and checks where the number can be added
input: the number and a pointer to the board
output: none
*/
void ForLoopForNumber(int number, Board *b)
{
	int rowNum = 0, columnNum = -3;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (columnNum == 9)
		{
			rowNum++;
			columnNum = -3;
		}
		columnNum++;
		if (CheckCube(rowNum, columnNum, number, *b))
			break;



	}
}


bool Solve(Board b)
{

}


