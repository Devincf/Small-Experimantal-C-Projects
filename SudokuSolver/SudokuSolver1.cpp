// SudokuSolver1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Sudoku.h"






int main()
{
	Sudoku s;
	s.Initialize();
	std::string test[9] = { 
		{ "xx3xxxxxx" },
		{ "xxx27xxx4" },
		{ "x69xxx8xx" },
		{ "xx1xxxx27" },
		{ "x9xxx8xxx" },
		{ "xxx56xxxx" },
		{ "xxxxx4xxx" },
		{ "xxx9xx74x" },
		{ "xxx9x6x5x" }};
	s.loadSudoku(test);
	s.Solve();
	int i;
	std::cin >> i;

    return 0;
}


