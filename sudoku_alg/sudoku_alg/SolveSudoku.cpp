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


bool SolveSoduko::CheckCube(int r, int c, int num, Board b)
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


int SolveSoduko::WhatIsMissingInCube(int r, int c, Board b)
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

int SolveSoduko::WhatIsMissingInRow(int r, Board b)
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

int SolveSoduko::WhatIsMissingInColumn(int c, Board b)
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



PlaceInfo SolveSoduko::FindFreePlace(std::vector<PlaceInfo> places, Board b)
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


std::vector<PlaceInfo> SolveSoduko::FindPlacesInCube(bool rows[], bool columns[], int rNum, int cNum)
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


PlaceInfo SolveSoduko::FindPlaceToAddNumber(int number, int c, int r, Board b)
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


void SolveSoduko::ForLoopForNumber(int number, Board *b)
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


void SolveSoduko::AddToRow(int row, int num, Board* b)
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

void SolveSoduko::AddToColumn(int column, int num, Board* b)
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

void SolveSoduko::AddToCube(int row, int col, int num, Board* b)
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



void SolveSoduko::RowsColumnsAndCubes(Board* b)
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
void SolveSoduko::Solve(Board *b)
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