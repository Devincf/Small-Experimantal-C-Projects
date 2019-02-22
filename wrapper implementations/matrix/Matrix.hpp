#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T>
std::array<T, N> createSubArrays(std::array<T, M> &inArr, size_t off = 0)
{
    std::array<T, N> temp;
    for (size_t i = 0; i < N; i++)
    {
        temp[i] = inArr[i * M / N + off];
    }
    return temp;
}

template <size_t N, typename T = double>
class Vector
{
  private:
    std::array<T, N> _vectorElements;

  public:
    //Vector(Vector &&) = default; uncomment => compiler error . not instantiable because no copy by reference constructor available
    Vector(const Vector &) = default;

    template <typename... Targs>
    Vector(Targs... args) : _vectorElements({args...}) {}

    Vector(const std::array<T, N> &iElem) : _vectorElements(iElem) {}

    constexpr size_t getDimension() { return N; }

    constexpr std::array<T, N> &getElements() { return _vectorElements; }

    constexpr void print()
    {
        for (size_t i = 0; i < N; i++)
        {
            std::cout << "[" << _vectorElements[i] << "]" << std::endl;
        }
    }

    constexpr T &operator[](const size_t i) { return _vectorElements[i]; }

    auto operator+(Vector<N, T> &&rhs)
    {
        std::array<T, N> temp;
        std::transform(rhs.getElements().begin(), rhs.getElements().end(), this->getElements().begin(), temp.begin(), std::plus<T>());
        return Vector<N>(temp);
    }

    auto operator*(const T &&rhs)
    {
        std::array<T, N> A;
        std::transform(_vectorElements.begin(), _vectorElements.end(), A.begin(),
                       std::bind1st(std::multiplies<T>(), rhs));
        return Vector<N>(A);
    }

    constexpr T operator*(Vector<N> &rhs)
    {
        return std::inner_product(rhs.getElements().begin(), rhs.getElements().end(), this->getElements().begin(), 0.0);
    }
    constexpr T operator*(Vector<N> &&rhs)
    {
        return std::inner_product(rhs.getElements().begin(), rhs.getElements().end(), this->getElements().begin(), 0.0);
    }
};

template <size_t N, size_t M, typename T = double>
class Matrix
{
  private:
    std::array<Vector<N>, M> _matrixGrid;

  public:
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) = default;

    Matrix(std::array<Vector<N>, M> &iGrid) : _matrixGrid(iGrid) {}

    Matrix(std::array<T, N * M> arr)
        : Matrix(std::make_index_sequence<N * M>{}, arr)
    {
    }
    template <size_t... Is>
    Matrix(std::index_sequence<Is...>, std::array<T, N * M> arr)
        : Matrix(arr[Is]...)
    {
    }
    template <typename... Ts>
    Matrix(Ts &&... vals)
        : Matrix(std::index_sequence_for<Ts...>{}, std::forward<Ts>(vals)...)
    {
    }
    template <size_t... Is, typename... Ts>
    Matrix(std::index_sequence<Is...>, Ts &&... vals)
    {
        std::array<T, N * M> arr;
        std::array<Vector<N>, M> vecs;
        (static_cast<void>(arr[Is] = vals), ...);
        for (size_t i = 0; i < M; i++)
        {
            vecs[i] = Vector<N>(createSubArrays<N>(arr, i));
            //vecs[i].print();
            //std::cout << std::endl;
        }
        _matrixGrid = std::array<Vector<N>, M>(vecs);
    }

    constexpr size_t getRowCount() { return N; }
    constexpr size_t getColCount() { return M; }

    constexpr std::array<Vector<N>, M>& getGrid() { return _matrixGrid; }

    constexpr void print()
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                std::cout << "[" << (*this)[j][i] << "]";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    auto transpose()
    {
        std::array<Vector<M>, N> vecs;
        for (size_t i = 0; i < N; i++)
        {
            std::array<T, M> arr;
            for (size_t j = 0; j < M; j++)
            {
                arr[j] = (*this)[j][i];
            }
            vecs[i] = Vector<M>(arr);
        }
        return Matrix<M, N, T>(vecs);
    }

    auto operator[](size_t index)
    {
        return _matrixGrid[index];
    }

    auto operator+(Matrix<N, M, T> &rhs)
    {
        std::array<T, N * M> temp;
        std::transform(rhs.getGrid().begin(), rhs.getGrid().end(), this->getGrid().begin(), temp.begin(), std::plus<T>());
        return Matrix<N, M, T>(temp);
    }

    template <template <size_t, size_t, typename> class A, size_t Q, size_t P>
    auto operator*(A<Q, P, T> &rhs)
    {
        if (M != Q)
            nullptr;
        std::array<T, N * P> temp{0};
        auto transpose = this->transpose();
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                temp[i*N + j] = transpose[i] * rhs[j];
            }
        }

        return Matrix<N, P, T>(temp);
    }
};

/*template <size_t N, size_t M, typename NumberType = double>
class Matrix
{
  public:
    using Value = NumberType;
    using Storage = std::array<NumberType, N * M>;
    using RowVec = Vector<M, NumberType>;
    using ColVec = RowVec;

  private:
    Storage mGrid;

  public:
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) = default;

    template <typename... Targs>
    Matrix(Targs... args) : mGrid({args...}) {}

    Matrix(const Storage &args) : mGrid(args) {}

    RowVec operator[](size_t index) const
    {
        return Row(index);
    }
    Value operator()(size_t Row, size_t Col) const
    {
        if (Row != 0 && Col != 0)
            return mGrid[(Col - 1) + M * (Row - 1)];
        throw;
    }

    constexpr size_t Height() { return N; };
    constexpr size_t Width() { return M; }

    Storage &data() { return mGrid; }

    RowVec Row(size_t index) const
    {
        if (index <= N && index != 0)
        {
            typename RowVec::Storage temp;
            for (auto i = 1; i <= M; i++)
                temp[i - 1] = (*this)(index, i);
            return RowVec(temp);
        }
        throw;
    }
    RowVec Col(size_t index) const
    {
        if (index <= N && index != 0)
        {
            typename RowVec::Storage temp;
            for (auto i = 1; i <= N; i++)
                temp[i - 1] = (*this)(i, index);
            return RowVec(temp);
        }
        throw;
    }

    void transpose()
    {
        Storage tmp;
        for (auto i = 0; i < N * M; i++)
        {
            int row = i / N;
            int col = i % M;
            tmp[i] = mGrid[M * col + row];
        }
        mGrid = tmp;
    }

    template <template <size_t, size_t, typename> class B, size_t I, size_t J, typename Type>
    auto operator*(B<I, J, Type> &b)
    {
        return mul(b);
    }

    auto operator*(Value val)
    {
        return mul(val);
    }
            template< template<size_t,size_t,typename>class B, size_t I, size_t J, typename Type>
        auto mul(B<I,J,Type>& b) -> decltype(Matrix<N, J, Value>{})
        {
            Matrix<N, J, Value> result;
            for (auto i = 0; i < N; ++i)
                for (auto j = 0; j < J; ++j)
                {
                    for (int k = 0; k < I; ++k)
                    {
                        int _a = M * i + k;
                        int _b = J * k + j;
                        result.data()[J * i + j] += this->mGrid[_a] * b.data()[_b];
                    }
                }
            return result;
        }

        Matrix mul(Value b)
        {
            Storage result;
            for (auto i = 0; i < N; ++i)
                for (auto j = 0; j < M; ++j)
                {
                    result[M*i + j] = mGrid[M*i + j] * b;
                }
            return { result };
        }

};
*/