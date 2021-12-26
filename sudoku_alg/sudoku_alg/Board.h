#pragma once

#include <iostream>


class Board
{
public:
	Board(std::string b);

	bool AddNumber(int number, int r, int c);
	bool CheckForRow(int rNum, int num);
	bool CheckForColumn(int cNum, int num);
	int HowManyMissingR(int rNum);
	int HowManyMissingC(int cNum);
	bool AddMissingR(int rNum);
	bool AddMissingC(int cNum);

private:
	int board[9][9];
	int number_amount[9];
};

