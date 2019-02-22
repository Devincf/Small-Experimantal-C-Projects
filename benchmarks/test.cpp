#include "benchmarks.hpp"
#include <thread>

class TestBenchmark : public Benchmark
{
    public:
    TestBenchmark():Benchmark("Test Benchmark")
    {
        run();
    }
    private:
    virtual void performBenchmark()
    {
        std::this_thread::sleep_for(2s);
    }
};

int main()
{
    TestBenchmark b;
    return 0;
}