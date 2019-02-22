#ifndef BENCHMARKS_HPP
#define BENCHMARKS_HPP

#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std::chrono_literals;

class Benchmark
{
    protected:
    Benchmark():Benchmark("unnamed"){}
    Benchmark(const std::string& name): _name(name)
    {
    }
    void run()
    {
        std::cout << "Starting Benchmark for " << _name << "\n";
        auto start = steady_clock::now();
        this->performBenchmark();
        auto end = steady_clock::now();
        std::cout << "Benchmark finished.\nElapsed time: " << duration_cast<nanoseconds>(end-start).count() << "ns \n";
    }
    ~Benchmark(){}
    protected:
    std::string _name;
    virtual void performBenchmark() = 0;
    
};

#endif