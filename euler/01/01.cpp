#include "../../benchmarks/benchmarks.hpp"

#include <thread>

#define RANGE 100000

/**
 * Problem:
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. 
 * The sum of these multiples is 23.
 * 
 * Find the sum of all the multiples of 3 or 5 below 1000.
 * */

static void calculateSum(int &sum, const size_t &range, const size_t &multiple)
{
    for (int i = 0; i < range; i+=multiple) sum += i;
}

class Euler01 : public Benchmark
{
  public:
    Euler01() : Benchmark("Euler 01 Benchmark")
    {
        run();
    }
    ~Euler01() {}
    virtual void performBenchmark()
    {
        //mt();
        st();
    }
    /**
     * Single threaded method
     * */
    void st()
    {
        int sum { 0 };
        for (int i = 0; i < RANGE; i++)
        {
            if(i%5==0||i%3==0)
                sum += i;
        }
        std::cout << sum << std::endl;
    }
    /**
     * Multi threaded method
     * Not worthwhile for a range smaller than ~100000 
     * at a bigger range you can start seeing improvements.
     * */
    void mt()
    {
        int sum1{0}, sum2{0},sum3{0};
        std::thread t1(calculateSum, std::ref(sum1), RANGE, 3);
        std::thread t2(calculateSum, std::ref(sum2), RANGE, 5);
        std::thread t3(calculateSum, std::ref(sum3), RANGE, 3*5);

        t1.join();
        t2.join();
        t3.join();
        const int finalSum = sum1 + sum2 -sum3;
        std::cout << " -- " << finalSum << std::endl;
    }
};

int main()
{
    Euler01 e;
    return 1;
}