#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <memory>
#include "util.hpp"
#include <thread>
#include <mutex>

#define THREADS 4
std::mutex mutex;
template <typename T>
class SimpleMatrix;
template <typename T = float>
static void multiplyPart(std::vector<T>* arr, const SimpleMatrix<T>& m1, const SimpleMatrix<T>& m2, const int begin, const int end)
{
    for (size_t i = begin; i < end; i++)
    {
        const size_t cols = m1[i].getSize();
        for (size_t j = 0; j < cols; j++)
        {
            mutex.try_lock();
            arr->at(i * cols + j) = m1[i] * m2[j];
            mutex.unlock();
        }
    }
}

template <typename T = float>
class SimpleVector
{
  private:
    std::vector<T> _elements;
    size_t _size;

  public:
    SimpleVector(size_t size) : _size(size)
    {
        for (size_t i = 0; i < size; i++)
        {
            _elements.push_back(randNumber<T>());
        }
    }
    SimpleVector(const std::vector<T>& vec) : _size(vec.size()), _elements(vec)
    {
    }

    const size_t &getSize() const { return _size; }
    const std::vector<T> &getElements() const { return _elements; }
    constexpr T operator[](const size_t i) const { return _elements.at(i); }


    constexpr SimpleVector<T> operator+(const SimpleVector<T>& rhs)
    {
        if(getSize() != rhs.getSize())
            return SimpleVector<T>(0);

        std::vector<T> temp;
        for (size_t i = 0; i < _size;i++)
        {
            temp.push_back((*this)[i] + rhs[i]);
        }
        return SimpleVector<T>(temp);
    }

    constexpr T operator*(const SimpleVector<T> &rhs) const
    {
        if(getSize() != rhs.getSize())
            return 0;
        return std::inner_product(rhs.getElements().begin(), rhs.getElements().end(), this->getElements().begin(), 0.0f);
    }
    constexpr T operator*(const SimpleVector<T> &&rhs) const
    {
        if(getSize() != rhs.getSize())
            return 0;
        return std::inner_product(rhs.getElements().begin(), rhs.getElements().end(), getElements().begin(), 0.0f);
    }

    void print(bool row = false) const
    {
        for (const auto &i : _elements)
        {
            if (row)
                std::cout << "[" << i << "]";
            else
                std::cout << "[" << i << "]" << std::endl;
        }
        std::cout << std::endl;
    }
};

template <typename T = float>
class SimpleMatrix
{
  private:
    std::vector<SimpleVector<T>> _elements;
    size_t _rows, _cols;

  public:
    SimpleMatrix(size_t rows, size_t cols) : _rows(rows), _cols(cols)
    {
        for (size_t i = 0; i < rows; i++)
            _elements.push_back(SimpleVector<T>(cols));
    }
    const size_t& getCols() const {return _cols;}
    const size_t& getRows() const {return _rows;}
    auto operator[](size_t index)const {return _elements.at(index);}

    SimpleMatrix(const std::vector<SimpleVector<T>>& vecs): _rows(vecs.size()), _cols(vecs.at(0).getSize()), _elements(vecs){}
    SimpleMatrix(size_t rows, size_t cols, const std::vector<T>&& vecs): _rows(rows), _cols(cols)
    {
        for(size_t i = 0;i<rows;i++)
        {  
            std::vector<T> vec;
            for(size_t j = 0;j<cols;j++)
                vec.push_back(vecs.at(i * cols + j));

            _elements.push_back(SimpleVector<T>(vec));
        }
    }
    auto multiplyMT(const SimpleMatrix<T>& rhs)
    {
        std::vector<T> vec(getRows() * rhs.getCols());
        auto transpose = this->transpose();
        std::array<std::thread, THREADS> threads;
        const int size_per_thread = _rows / THREADS;
        for (size_t c = 0; c < THREADS; c++)
        {
            const int begin = c * size_per_thread;
            const int end = begin + size_per_thread;
            //std::cout << "beg " << begin << " - end " << end << std::endl;
            threads[c] = std::thread(multiplyPart<T>, &vec, std::ref(transpose), std::ref(rhs), begin, end);
        }
        for (size_t i = 0; i < THREADS; i++)
        {
            threads[i].join();
        }
        return SimpleMatrix<T>(getRows(), rhs.getCols(), std::move(vec));
    }
    const SimpleMatrix<T> transpose()
    {
        std::vector<SimpleVector<T>> vecs;
        for (size_t i = 0; i < _rows; i++)
        {
            std::vector<T> vec;
            for (size_t j = 0; j < _cols; j++)
            {
                vec.push_back((*this)[j][i]);
            }
            vecs.push_back(SimpleVector<T>(vec));
        }
        return SimpleMatrix<T>(vecs);
    }

    auto operator*(SimpleMatrix<T> &rhs)
    {
        if (rhs.getRows() != getCols())
            SimpleMatrix<T>(0,0,{});

        std::vector<T> temp;
        auto transpose = this->transpose();
        for (size_t i = 0; i < _rows; i++)
        {
            for (size_t j = 0; j < _cols; j++)
            {
                temp.push_back(transpose[j] * rhs[i]);
            }
        }

        return SimpleMatrix<T>(_rows, rhs.getCols(), std::move(temp));
    }

    

    void print() const
    {
        for (const auto &i : _elements)
        {
            i.print(true);
        }
    }
};
