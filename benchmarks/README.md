# Benchmarking

Simple implementation of a benchmarking class

# How to:

Create a class with Benchmark as a superclass.

Initialize whatever you wanna initialize inside the constructor and add a call to
```cpp
Benchmark::run()
```

Afterwards put whatever you want to benchmark inside the virtual function
```cpp
Benchmark::performBenchmark();
```

finally initialize your Benchmark class.


For more information check the example in test.cpp