#include "stdafx.h"
#include "Sudoku.h"

#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <time.h>


Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}

void Sudoku::Initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fields[i][j].number = 0;
			for (int k = 1; k < 10; k++)
			{
				fields[i][j].possibilities[k - 1] = true;
			}
		}
	}
}

void Sudoku::loadSudoku(const std::string s[9])
{
	for (int i = 0; i < 9; i++) {

	}
}

bool Sudoku::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void Sudoku::checkAll()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (fields[i][j].number == 0)
			{
				return;
			}
		}
	}
	solved = true;
}

void Sudoku::showCurrSudoku()
{
	for (int i = 0; i < 9; i++)
	{
		if (i == 0) {
			std::cout << std::endl << " |||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		}

		for (int j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
			{
				std::cout << " ||| ";
			}
			else {
				std::cout << " | ";
			}
			std::cout << fields[i][j].number;

			if (j == 8) {
				std::cout << " |||";
			}
		}
		if ((i+1) % 3 == 0) {
			std::cout << std::endl << " |||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		}
		else {
			std::cout << std::endl << " |||___|___|___|||___|___|___|||___|___|___|||" << std::endl;
		}
	}
}

void Sudoku::showCurrSudokuDebug()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j % 3 == 0) {
				std::cout << "|||";
			}
			else {
				std::cout << "|";
			}
			std::cout << "(" <<  fields[i][j].number << ")";
			
			for (int lm = 0; lm < 9; lm++)
			{
				if (fields[i][j].possibilities[lm] == 1)
				{
					std::cout << lm + 1;
				}
			}
		}
		std::cout << std::endl << "___________________________________________________________________________________________________" << std::endl;
	}
}

void Sudoku::Solve()
{
	long int start = GetTickCount();
	showCurrSudoku();
	while (!solved)
	{
		system("cls");
		for (int i = 0; i < 9; i++)
		{
			for (int k = 0; k < 9; k++)
			{
				checkRow(i, k);
				checkPossibilities(k,i);
			}
			checkBox(i);
		}
		checkAll();
		showCurrSudoku();
		Sleep(100);
	}
	long int end = GetTickCount();
	long int elapsed = end - start;
	std::cout << elapsed << "ms since start of Program" << std::endl;
}

void Sudoku::checkRow(int y,int x)
{
	int amt[9][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	if (fields[y][x].number == 0)
	{
		return;
	}
	//vert check

	int amt2[9][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	for (int i = 0; i < 9; i++)
	{
		if (fields[i][x].number == 0)
		{
			fields[i][x].possibilities[fields[y][x].number - 1] = false;
		}
		for (int loop2 = 0; loop2 < 9; loop2++)
		{
			if (fields[y][i].possibilities[loop2])
			{
				amt2[loop2][0]++;
				amt2[loop2][1] = y;
				amt2[loop2][2] = i;
			}
		}
	}
	
	for (int loop3 = 0; loop3 < 9; loop3++)
	{
		if (amt2[loop3][0] == 1)
		{
			fields[amt2[loop3][1]][amt2[loop3][2]].number = loop3 + 1;
			for (int it = 0; it < 9; it++)
			{
				fields[amt2[loop3][1]][amt2[loop3][2]].possibilities[it] = false;
			}
		}
	}

	//horizontal check
	for (int i = 0; i < 9; i++)
	{
		if (fields[y][i].number == 0)
		{
			fields[y][i].possibilities[fields[y][x].number - 1] = false;
		}
		for (int loop2 = 0; loop2 < 9; loop2++)
		{
			if (fields[y][i].possibilities[loop2])
			{
				amt[loop2][0]++;
				amt[loop2][1] = y;
				amt[loop2][2] = i;
			}
		}
	}
	for (int loop3 = 0; loop3 < 9; loop3++)
	{
		if (amt[loop3][0] == 1)
		{
			fields[amt[loop3][1]][amt[loop3][2]].number = loop3 + 1;
			for (int it = 0; it < 9; it++)
			{
				fields[amt[loop3][1]][amt[loop3][2]].possibilities[it] = false;
			}
		}
	}
}

void Sudoku::checkBox(int box)
{
	int x = box;
}

void Sudoku::checkPossibilities(int x, int y)
{
	int temp = 0;
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		if (fields[y][x].possibilities[i])
		{
			temp = i + 1;
			count++;
		}
	}
	if (count == 1)
	{
		fields[y][x].number = temp;
	}

	//check Box for only poss

}
