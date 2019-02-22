#include <chrono>
#include <iostream>

#define matrix_size 5000

//#include "Matrix2.hpp"
#include "SimpleMatrix.hpp"
#include "util.hpp"
using namespace std::chrono;
using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    srand (time(NULL));

    int range = 10;

	/* do some stuff here
    TYPE* arr = new TYPE[SIZE*SIZE];
    TYPE* arr2 = new TYPE[SIZE*SIZE];
    for(size_t i=0;i<SIZE*SIZE;i++){
        arr[i] = randNumber(range);
    }
    for(size_t i=0;i<SIZE*SIZE;i++){
        arr2[i] = randNumber(range);
    }
        auto start = steady_clock::now();
        Matrix v(arr),v2(arr2);

        Matrix v3 = v * v2;
        auto end = steady_clock::now();
        printElapsed("Matrix multiplication default transposed",end-start);
        start = steady_clock::now();

        Matrix v4 = v.multiplyMT(v2);
        end = steady_clock::now();
        printElapsed("Matrix multiplication MT transposed",end-start);
        start = steady_clock::now();

        */
    auto start = steady_clock::now();
    SimpleMatrix<float> m (matrix_size,matrix_size);
    SimpleMatrix<float> m2 (matrix_size,matrix_size);
    auto test = m * m2;
    auto end = steady_clock::now();
    printElapsed("Matrix multiplication", end-start);

    std::this_thread::sleep_for(2s);

    start = steady_clock::now();
    test = m.multiplyMT(m2);
    end = steady_clock::now();
    printElapsed("Matrix multiplication MT", end-start);

    return 1;
}