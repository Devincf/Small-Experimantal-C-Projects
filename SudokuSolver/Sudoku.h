#pragma once

#include <iostream>

struct Field
{
	int number;
	bool possibilities[9];
};

class Sudoku
{
private:
	bool is_number(const std::string&);

	bool solved = false;

	void checkAll();
public:
	Field fields[9][9];

	void Initialize();

	void showCurrSudoku();
	void showCurrSudokuDebug();

	void Solve();

	void checkRow(int, int);
	void checkBox(int);
	void checkPossibilities(int, int);

	void loadSudoku(const std::string[9][9]);
	Sudoku();
	~Sudoku();
};

