#pragma once

#include "Board.h"
#include "Structs.h"
#include <vector>

class SolveSoduko
{
public:

	SolveSoduko(std::string board);

	/*
	this function is the loop to solve the sudoku
	input: a pointer to the board
	output: none
	*/
	void Solve();

	/*
	this function gets the row and column of the first place in the cube and the number to check, and checks is the number is in the cube
	input: row number, column number, the number to check and the board
	output: if the number is in the cube or not
	*/
	bool CheckCube(int r, int c, int num);


	/*
	this function gets the numbers that exist in the cube, row or column
	the function will return 0 if there is more than one number missing
	otherwise it will return the missing number
	*/
	int ReturnMissing(int exists[], int count);

	/*
	this function will check what is the missing number in the cube,
	if there is more than 1 number missing, it will return 0
	input: the row and column of the cube and the board
	output: if only one number is missing -> the number (1->9)
			if there is more than 1 number missing -> 0
	*/
	int WhatIsMissingInCube(int r, int c);
	/*
	this function will check what is the missing number in the row,
	if there is more than 1 number missing, it will return 0
	input: the row and the board
	output: if only one number is missing -> the number (1->9)
			if there is more than 1 number missing -> 0
	*/
	int WhatIsMissingInRow(int r);
	/*
	this function will check what is the missing number in the column,
	if there is more than 1 number missing, it will return 0
	input: the column and the board
	output: if only one number is missing -> the number (1->9)
			if there is more than 1 number missing -> 0
	*/
	int WhatIsMissingInColumn(int c);


	/*
	this function gets the vector of the PlaceInfo of where the number can be added
	the function will filter the full places(the places that already have a number)
	input: the vector of PlaceInfo and the board
	output: if there is only 1 free place, it will sent this place
			else it will sent a PlaceInfo where the row and column numbers are 100 (not a valid place)
	*/
	PlaceInfo FindFreePlace(std::vector<PlaceInfo> places);

	/*
	this function gets the rows and columns of the cube and searches for places to put the number in
	input: a bool array for the rows and a bool array for the columns
	output: a vector of places to put the number in
	*/
	std::vector<PlaceInfo> FindPlacesInCube(bool rows[], bool columns[], int rNum, int cNum);

	/*
	this function will get a cube that does not have the number and will find the place to add the number
	input: the number, the row and column of the cube and the board
	output: a PlaceInfo for the place to add the number
			if there is more than one place, it will return a PlaceInfo with the number 0
	*/
	PlaceInfo FindPlaceToAddNumber(int number, int c, int r);

	/*
	this function goes over the cubes and checks where the number can be added, and if it can, it adds it
	input: the number and a pointer to the board
	output: none
	*/
	void ForLoopForNumber(int number);

	/*
	this function gets the row, number and board, and adds the number to the row
			***** this function only gets a row with one number missing *****

	input: the row number, the number to add and a pointer to the board
	output: none
	*/
	void AddToRow(int row, int num);
	/*
	this function gets the column, number and board, and adds the number to the column
			***** this function only gets a column with one number missing *****

	input: the column number, the number to add and a pointer to the board
	output: none
	*/
	void AddToColumn(int column, int num);
	/*
	this function gets the row and column of the column, number and board, and adds the number to the cube
			***** this function only gets a cube with one number missing *****

	input: the row number, the column number, the number to add and a pointer to the board
	output: none
	*/
	void AddToCube(int row, int col, int num);


	/*
	this function goes over the cubes, rows and columns to see if there is only one number missing. if so, it adds it
	input: a pointer to the board
	output: none
	*/
	void RowsColumnsAndCubes();


private:
	Board *b;
};

