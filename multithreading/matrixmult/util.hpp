#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <chrono>
using namespace std::chrono;

__always_inline double randNumber(const int& range)
{
    return rand() % range;
}

template <typename T = float>
__always_inline T randNumber(const float& range = 100)
{
    return static_cast <T> (rand()) / (static_cast <T> (RAND_MAX/range));
}

void printElapsed(const std::string& str, duration<int64_t, std::nano>&& timeElapsed){
    std::cout << str << " took " << duration_cast<seconds>(timeElapsed).count() << " s or " 
    << duration_cast<milliseconds>(timeElapsed).count() << " ms or "<< duration_cast<nanoseconds>(timeElapsed).count() << " ns"<< std::endl;
}

#endif