#include "IsSudokuSolved.h"

IsSudokuSolved::IsSudokuSolved(std::string board)
{
	this->b = new Board(board);
	this->stdBoard = board;
}

int IsSudokuSolved::CountInCube(int r, int c, int num)
{
	int counter = 0;
	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (this->b->board[r + i][c + j] == num)
				counter++;
		}
	}
	
	return counter;
}

int IsSudokuSolved::CountInRow(int r, int num)
{
	int counter = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (this->b->board[r][i] == num)
			counter++;
	}

	return counter;
}

int IsSudokuSolved::CountInColumn(int c, int num)
{
	int counter = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (this->b->board[i][c] == num)
			counter++;
	}

	return counter;
}


bool IsSudokuSolved::Sudoku()
{
	for (size_t i = 1; i <= BOARD_SIZE; i++)
	{
		if (this->b->CountNumber(this->stdBoard, i) != 9)
			return false;
	}

	for (size_t i = 1; i <= BOARD_SIZE; i++) // runs through the numbers
	{
		for (size_t j = 0; j < BOARD_SIZE; j++) // for each number -> all the rows and columns
		{
			if (CountInColumn(j, i) != 1 || CountInRow(j, i) != 1)
				return false;
		}
		 
		for (size_t k = 0; k < BOARD_SIZE; k+=3) // for each number -> all the cubes
		{
			for (size_t j = 0; j < BOARD_SIZE; j+=3)
			{
				if (CountInCube(k, j, i) != 1)
					return false;
			}
		}
	}

	return true;
}
