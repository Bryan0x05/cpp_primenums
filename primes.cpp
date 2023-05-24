#include "primes.hpp"
#include <cmath>
//TODO: Setup unit testing using catch2(?) or Google test
//TODO: Setup multi-threading
//TODO: Optimizie program(better, more effecient variable loop step)
bool isPrime(std::vector<int> primes, int num)
{
    if (num % 2 != 0 && num % 3 != 0)
    {
        for (int prime : primes)
        {
            if (num % prime == 0)
                return false;
        }
        return true;
    }
    return false;
}

std::vector<int> findPrimes(int upperBound){
    std::vector<int> primes;

    //inclusive of upperBound
    for(int index = 2; index <= upperBound; index++){
        if(index == 2 || index == 3){
            primes.emplace_back(index);
        }
        else{
            if(isPrime(primes,index)){
                primes.emplace_back(index);
            }
        }
    }
    return primes;
}
