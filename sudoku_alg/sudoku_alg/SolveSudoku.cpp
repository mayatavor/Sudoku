#include <iostream>
#include <list>
#include <ctime>
#include <string>
#include "Board.h"
#include "Structs.h"
#include <vector>
#include "SolveSudoku.h"

#define BOARD_SIZE 9
#define CUBE_SIZE 3


SolveSoduko::SolveSoduko(std::string board)
{
	this->b = new Board(board);
}

bool SolveSoduko::CheckCube(int r, int c, int num)
{
	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (this->b->board[r + i][c + j] == num)
				return true;
		}
	}
	return false;
}

int SolveSoduko::ReturnMissing(int exists[], int count)
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


int SolveSoduko::WhatIsMissingInCube(int r, int c)
{
	int numbers_exist[BOARD_SIZE] = { 0,0,0,0,0,0,0,0 };
	int numbers_count = 0;

	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (this->b->board[i][j] != 0)
			{
				numbers_count++;
				numbers_exist[this->b->board[i][j] - 1] = this->b->board[i][j];
			}
		}
	}

	return ReturnMissing(numbers_exist, numbers_count);
}

int SolveSoduko::WhatIsMissingInRow(int r)
{
	int numbers_exist[BOARD_SIZE] = { 0,0,0,0,0,0,0,0 };
	int numbers_count = 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (this->b->board[r][i] != 0)
		{
			numbers_count++;
			numbers_exist[this->b->board[r][i] - 1] = this->b->board[r][i];
		}
	}

	return ReturnMissing(numbers_exist, numbers_count);
}

int SolveSoduko::WhatIsMissingInColumn(int c)
{
	int numbers_exist[BOARD_SIZE] = { 0,0,0,0,0,0,0,0 };
	int numbers_count = 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (this->b->board[i][c] != 0)
		{
			numbers_count++;
			numbers_exist[this->b->board[i][c] - 1] = this->b->board[i][c];
		}
	}

	return ReturnMissing(numbers_exist, numbers_count);
}



PlaceInfo SolveSoduko::FindFreePlace(std::vector<PlaceInfo> places)
{
	std::vector<PlaceInfo> free_places;
	for (size_t i = 0; i < places.size(); i++)
	{
		if (this->b->board[places[i].rowNumber][places[i].columnNumber] == 0)
			free_places.push_back(PlaceInfo(places[i]));
	}

	if (free_places.size() == 1)
		return free_places[0];
	return PlaceInfo(100, 100);
}


std::vector<PlaceInfo> SolveSoduko::FindPlacesInCube(bool rows[], bool columns[], int rNum, int cNum)
{
	std::vector<PlaceInfo> *places = new std::vector<PlaceInfo>();

	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		if (rows[i] == true)
			continue;
		for (size_t j = 0; j < CUBE_SIZE; j++)
		{
			if (columns[j] == true)
				continue;
			places->push_back(PlaceInfo(i, j));
		}
	}

	return *places;
}


PlaceInfo SolveSoduko::FindPlaceToAddNumber(int number, int c, int r)
{
	bool rows[] = { false,false,false };
	bool columns[] = { false,false,false };

	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		rows[i] = this->b->CheckForRow(r+i, number);
	}
	for (size_t i = 0; i < CUBE_SIZE; i++)
	{
		columns[i] = this->b->CheckForColumn(c+i, number);
	}

	std::vector<PlaceInfo> places = FindPlacesInCube(rows, columns, r, c);
	return FindFreePlace(places);
}


void SolveSoduko::ForLoopForNumber(int number)
{
	int rowNum = 0, columnNum = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (columnNum == 9)
		{
			rowNum += 3;
			columnNum = 0;
		}
		if (CheckCube(rowNum, columnNum, number))
			continue;

		PlaceInfo place = FindPlaceToAddNumber(number, rowNum, columnNum);

		if (place.columnNumber == 100)
			continue;

		place.number = number;

		b->AddNumber(PlaceInfo(place.number, place.rowNumber, place.columnNumber));
		columnNum += 3;
	}
}


void SolveSoduko::AddToRow(int row, int num)
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

void SolveSoduko::AddToColumn(int column, int num)
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

void SolveSoduko::AddToCube(int row, int col, int num)
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



void SolveSoduko::RowsColumnsAndCubes()
{
	int now = 0;

	//adding to the rows
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		now = WhatIsMissingInRow(i);
		if (now == 0)
			continue;
		
		AddToRow(i, now);
	}

	//adding to the column
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		now = WhatIsMissingInColumn(i);
		if (now == 0)
			continue;

		AddToColumn(i, now);
	}

	//adding to the cube
	for (size_t i = 0; i < CUBE_SIZE; i+=3)
	{
		for (size_t j = 0; j < CUBE_SIZE; j+=3)
		{
			now = WhatIsMissingInCube(i, j);
			if (now == 0)
				continue;

			AddToCube(i, j, now);
		}
	}

}



/*
this function is the loop to solve the sudoku
input: a pointer to the board
output: none
*/
void SolveSoduko::Solve()
{
	this->b->PrintBoard();
	while (b->GetCount() < 81)
	{
		for (size_t i = 1; i <= BOARD_SIZE; i++)
		{
			ForLoopForNumber(i);
		}
		RowsColumnsAndCubes();

		this->b->PrintBoard();
	}
}