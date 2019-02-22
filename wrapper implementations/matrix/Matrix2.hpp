#ifndef MATRIX2_HPP
#define MATRIX2_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>

#define SIZE 5000
#define TYPE int

#define THREADS 4

std::mutex mutex;
class Matrix;
static void multiplyPart(TYPE*, Matrix&, Matrix&, int, int);

class Vector
{
  public:
    TYPE *elements = nullptr;

    ~Vector()
    {
        if(elements != nullptr){
            delete[] elements;
            elements = nullptr;
        }
    }

    Vector(TYPE *arr)
    {
        elements = arr;
    }
    Vector()
    {
        elements = new TYPE[SIZE]{0};
    }

    void print()
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            std::cout << "[" << elements[i] << "]" << std::endl;
        }
        std::cout << std::endl;
    }

    TYPE &operator[](const size_t i) const
    {
        return this->elements[i];
    }

    TYPE operator*(const Vector &rhs)
    {
        //return std::inner_product(rhs.elements.begin(), rhs.elements.end(), this->elements.begin(), 0);
        TYPE sum = 0;
        for (size_t i = 0; i < SIZE; i++)
        {
            sum += (*this)[i] * rhs[i];
        }
        return sum;
    }

    void operator=(const Vector& rhs)
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            elements[i] = rhs[i];
        }
    }

    Vector operator+(Vector &rhs)
    {
        Vector v;
        for (size_t i = 0; i < SIZE; i++)
        {
            v[i] = (*this)[i] + rhs[i];
        }
        return v;
    }

    Vector operator*(const TYPE &rhs)
    {
        Vector v;
        for (size_t i = 0; i < SIZE; i++)
        {
            v[i] = (*this)[i] * rhs;
        }
        return v;
    }
};
class Matrix
{
  public:
    Vector *elements = nullptr;

    Matrix()
    {
        elements = new Vector[SIZE];
    }
    ~Matrix()
    {
        if(elements != nullptr){
            delete[] elements;
            elements = nullptr;
        }
    }

    Matrix(Vector *arr) : elements(arr)
    {
        elements = new Vector[SIZE];
        elements = arr;
    }
    Matrix(TYPE *arr)
    {
        elements = new Vector[SIZE];

        for (size_t i = 0; i < SIZE; i++)
        {
            TYPE *temp = new TYPE[SIZE];
            for (size_t j = 0; j < SIZE; j++)
            {
                temp[j] = arr[j * SIZE + i];
            }
            elements[i] = Vector(temp);
        }
    }

    void print()
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                std::cout << "[" << (*this)[j][i] << "]";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    Vector &operator[](const size_t i) const
    {
        return this->elements[i];
    }

    auto transpose()
    {
        Vector *vecs = new Vector[SIZE];
        for (size_t i = 0; i < SIZE; i++)
        {
            TYPE *arr = new TYPE[SIZE];
            for (size_t j = 0; j < SIZE; j++)
            {
                arr[j] = (*this)[j][i];
            }
            vecs[i] = Vector(arr);
        }
        return Matrix(vecs);
    }

    Matrix operator+(Matrix &rhs)
    {
        Matrix m;
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                m[i][j] = (*this)[i][j] + rhs[i][j];
            }
        }
        return m;
    }

    Matrix operator*(const TYPE &rhs)
    {
        Matrix m;
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                m[i][j] = (*this)[i][j] * rhs;
            }
        }
        return m;
    }

    Matrix operator*(Matrix& rhs)
    {
        TYPE *temp = new TYPE[SIZE * SIZE];
        auto transpose = this->transpose();
        for (size_t i = 0; i < SIZE; i++)
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                temp[i * SIZE + j] = transpose[i] * rhs[j];
            }
        }
        return Matrix(temp);
    }

    Matrix multiplyMT(Matrix& rhs)
    {
        TYPE *temp = new TYPE[SIZE * SIZE];
        auto transpose = this->transpose();
        std::array<std::thread, THREADS> threads;
        const int size_per_thread = SIZE / THREADS;
        for (size_t c = 0; c < THREADS; c++)
        {
            const int begin = c * size_per_thread;
            const int end = begin + size_per_thread;
            //std::cout << "beg " << begin << " - end " << end << std::endl;
            threads[c] = std::thread(multiplyPart, temp, std::ref(transpose), std::ref(rhs), begin, end);
        }
        for (size_t i = 0; i < THREADS; i++)
        {
            threads[i].join();
        }
        return Matrix(temp);
    }
};


static void multiplyPart(TYPE *arr, Matrix& m1, Matrix& m2, int begin, int end)
{
    for (size_t i = begin; i < end; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            mutex.try_lock();
            arr[i * SIZE + j] = m1[i] * m2[j];
            mutex.unlock();
        }
    }
}

#endif