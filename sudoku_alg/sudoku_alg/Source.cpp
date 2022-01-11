#include <iostream>
#include <list>
#include <string>
#include "Board.h"
#include "Structs.h"


int main()
{
	std::string board = "427100068005006300603000100200010400340067051801050020090000730704300209032094600";

	Board *b = new Board(board);

	delete b;
	return 0;
}

