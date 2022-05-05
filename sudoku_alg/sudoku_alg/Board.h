#pragma once

#include <iostream>
#include <algorithm>
#include "Structs.h"

#define BOARD_SIZE 9
#define CUBE_SIZE 3

class Board
{
public:
	Board(std::string b);

	/*
	if the program found where to put a number, the function will put the number in the correct place and add 1 to the number count
	input: the number to add, the row number and the column number
	output: void
	*/
	void AddNumber(PlaceInfo);

	/*
	this function checks if the number is in the row
	input: the number and the row
	output: if the number already exists in the row or not
	*/
	bool CheckForRow(int rNum, int num);

	/*
	this function checks if the number is in the column
	input: the number and the column
	output: if the number already exists in the column or not
	*/
	bool CheckForColumn(int cNum, int num);

	/*
	prints the board
	*/
	void PrintBoard();

	//starters
	int CountNumber(std::string b, int number);

	//getter
	int GetCount();

	int board[9][9];

private:
	int number_amount[9];
	int number_count;
};

