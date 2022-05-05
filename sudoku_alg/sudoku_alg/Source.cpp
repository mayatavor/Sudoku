#include <iostream>
#include <list>
#include <string>
#include "Board.h"
#include "Structs.h"
#include "SolveSudoku.h"
#include "IsSudokuSolved.h"

//int main()
//{
//	std::string board = "427100068005006300603000100200010400340067051801050020090000730704300209032094600"; //works
//	//std::string boardC = "427139568915876342683542197256918473349267851871453926598621734764385219132794685"; //works
//	//std::string board = "640030007501070900000049610004908060080003020062400000400157030208300040750000096"; //works
//	//std::string board = "800135070020040830060708040000470908240080000038000005080604100900007204005810006"; //works
//	//std::string board = "004860030001000090800009060500206001027001000000043006050000000009000400000400015"; //does not word, hard level
//
//	SolveSoduko *solve = new SolveSoduko(board);
//
//	solve->Solve();
//
//	delete solve;
//	return 0;
//}

int main()
{
	//std::string boardC = "427139568915876342683542197256918473349267851871453926598621734764385219132794685"; //true
	std::string boardC = "427139568915876342683542197256918473349276851871453926598621734764385219132794685"; //false

	IsSudokuSolved* sudoku = new IsSudokuSolved(boardC);

	if(sudoku->Sudoku())
		std::cout << "true";
	else
		std::cout << "false";

	delete sudoku;
	return 0;
}

