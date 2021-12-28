#include <iostream>
#include <list>
#include <string>
#include "Board.h"
#include "Structs.h"

#define BOARD_SIZE 9


/*
this function gets the row and column of the first place in the cube and the number to check, and checks is the number is in the cube
input: row number, column number, the number to check and the board
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


bool solve(Board b)
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{

	}
}



bool Solve(Board b)
{
	

}


