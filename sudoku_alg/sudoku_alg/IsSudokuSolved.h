#pragma once

#include "Board.h"
#include "Structs.h"
#include <vector>

class IsSudokuSolved
{
public:

	IsSudokuSolved(std::string board);

	/*
	this function is the loop to solve the sudoku
	input: a pointer to the board
	output: none
	*/
	bool Sudoku();


	/*
	this function gets the row and column of the first place in the cube and the number to check, and checks is the number is in the cube
	input: row number, column number, the number to check and the board
	output: if the number is in the cube or not
	*/
	int CountInCube(int r, int c, int num);
	/*
	this function will check what is the missing number in the row,
	if there is more than 1 number missing, it will return 0
	input: the row and the board
	output: if only one number is missing -> the number (1->9)
			if there is more than 1 number missing -> 0
	*/
	int CountInRow(int r, int num);
	/*
	this function will check what is the missing number in the column,
	if there is more than 1 number missing, it will return 0
	input: the column and the board
	output: if only one number is missing -> the number (1->9)
			if there is more than 1 number missing -> 0
	*/
	int CountInColumn(int c, int num);



private:
	Board* b;
	std::string stdBoard;
};

