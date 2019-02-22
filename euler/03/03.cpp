#include "../../benchmarks/benchmarks.hpp"
#include <vector>
#include <map>
/**
 * Problem:
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600851475143 ?
 * */
#define NUMBER 600851475143
static std::map<size_t,bool> primes;

int checkPrimeNumber(const size_t& n)
{
  for(size_t i = 2; i <= n/2; ++i)
  {
      if(n%i == 0)
      {
          return i;
      }
  }
  return false;
}

class Euler03 : public Benchmark
{
    std::vector<size_t> prime_factors;
  public:
    Euler03() : Benchmark("Euler 03 Benchmark")
    {
        run();
    }
    ~Euler03() {}

    virtual void performBenchmark()
    {
        
    }

    void solveRec(const size_t& n )
    {
        if(primes[n]){
            prime_factors.push_back(n);
            return;
        }else
        {
            for(size_t i=0;i<n/2;i++)
            {

            }
        }
        

    }

};

int main()
{
    //precalc primes
    for(size_t i =1;i<NUMBER;i+=2)
    {
        if(checkPrimeNumber(i))   
            primes.insert(std::pair<size_t,bool>(i,true));
    }

    Euler03 e;
    return 1;
}