// lernen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <random>
#include <Windows.h>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
string tostr(const T& t) {
	stringstream ss;
	ss << t;
	return ss.str();
}

template<typename T, int N>
const int getArrSize (const T Arr[N]) {
	return sizeof(Arr) / sizeof(Arr[0]);
}

template<int N>
const void Print(const int(&arrToSort)[N]) {
	for (int i = 0; i < ARRAYSIZE(arrToSort);) {
		cout << ++i << ". Value : " << arrToSort[i - 1] << endl;
	}
}

template<int N>
const void QuickSwap(const int &i, const int &j, int (&a)[N]) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

template<int N>
void BubbleSort(int(&arrToSort)[N]) {
	bool swapped;
	do {
		swapped = false;

		for (size_t i = 0; i < ARRAYSIZE(arrToSort) - 1;i++) {
			if (arrToSort[i] > arrToSort[i + 1]) {
				swapped = true;
				QuickSwap(i, (i + 1), arrToSort);
			}
		}
	} while (swapped);
}

template<int N>
void QuickSort(int(&arrToSort)[N], const int &left, const int &right) {
	int i = left;
	int j = right;
	int pivot = arrToSort[(left + right) / 2];
	while (left<j || i<right)
	{
		while (arrToSort[i]<pivot)
			i++;
		while (arrToSort[j]>pivot)
			j--;
		if (j >= i) {
			QuickSwap(i, j, arrToSort);
			i++;
			j--;
		}
		else {
			if (left<j)
				QuickSort(arrToSort, left, j);
			if (i<right)
				QuickSort(arrToSort, i, right);
			return;
		}
	}
}

void sort1() {

	double duration, totalSortDuration = 0, totalLoadDuration = 0;
	const int arrsize = 30;
	const unsigned short runs = 5000;
	for (int i = 0; i < runs; i++) {

		int arr[arrsize];

		cout << "Started Generating Random Numbers and loading into Array for RUN[" + tostr(i) + "]...";
		std::clock_t start = clock();
		for (int i = 0; i < arrsize; i++) {
			arr[i] = rand() % arrsize + 1;
		}

		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		totalLoadDuration += duration;
		cout << "done in " << duration << "seconds" << endl << endl;

		//cout << "Unsorted Array"<< endl;
		//Print(arr);


		cout << "Starting the Sorting Algorithm with : " << arrsize << " Items in Array" << endl;
		start = clock();
		QuickSort(arr, 0, arrsize - 1);
		//BubbleSort(arr);

		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		totalSortDuration += duration;
		cout << "Sorting finished - Took " << duration << " seconds to finish." << endl << endl;

		//cout << "Sorted Array" << endl << endl;
		//Print(arr);
	}
	cout << "To Sort " << arrsize << " Items for " << runs << " amount of times. It took : " << totalSortDuration << " seconds. - Average Time : " << totalSortDuration / runs << endl;
	cout << "To Load " << arrsize << " Items for " << runs << " amount of times. It took : " << totalLoadDuration << " seconds. - Average Time : " << totalLoadDuration / runs << endl;
}

int main()
{
	sort1();

	getchar();

}

