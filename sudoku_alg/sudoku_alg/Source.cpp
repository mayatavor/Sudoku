#include <iostream>
#include <list>
#include <string>
#include "Board.h"
#include "Structs.h"
#include "SolveSudoku.h"

int main()
{
	std::string board = "427100068005006300603000100200010400340067051801050020090000730704300209032094600";

	SolveSoduko *solve = new SolveSoduko(board);

	solve->Solve();

	delete solve;
	return 0;
}

