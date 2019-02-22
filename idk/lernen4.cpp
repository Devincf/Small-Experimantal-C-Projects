// lernen4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<int> test[2];

	test[0] = vector<int>(20);

	for (auto i : test[0]) {
		cout << "number : " << i << endl;
	}

	for (int i = 0; i < 20; i++) {
		test[0].pop_back();
	}
	cout << "BLLBALBLBAL" << endl;
	for (auto i : test[0]) {
		cout << "number : " << i << endl;
	}

    return 0;
}

