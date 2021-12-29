#pragma once

#include <iostream>
#include <algorithm>
#include "Structs.h"

#define BOARD_SIZE 9

class Board
{
public:
	Board(std::string b);

	/*
	if the program found where to put a number, the functio will put the number in the correct place and add 1 to the number count
	input: the number to add, the row number and the column number
	output: if the number was added successfully or not
	*/
	bool AddNumber(PlaceInfo);

	/*
	this functio checks if the number is in the row
	input: the number and the row
	output: if the number already exists in the row or not
	*/
	bool CheckForRow(int rNum, int num);

	/*
	this functio checks if the number is in the column
	input: the number and the column
	output: if the number already exists in the column or not
	*/
	bool CheckForColumn(int cNum, int num);
	int HowManyMissingR(int rNum);
	int HowManyMissingC(int cNum);
	bool AddMissingR(int rNum);
	bool AddMissingC(int cNum);


	//starters
	int CountNumber(std::string b, int number);

	int board[9][9];
private:
	int number_amount[9];
};

