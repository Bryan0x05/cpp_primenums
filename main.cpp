#include <iostream>
#include <limits>
#include "primes.hpp"
//main to user input and then call the primes function
int main(int argc, char** argv){
    std::cout << "This program finds prime numbers starting from 2, then going up to a user defined upper bound(inclusive)" << std::endl;
    int upperBound;
        // if no command line input
        if (argc != 2)
    {
        std::cout << "Please enter an integer >= 2 for the upper bound: ";
        //input protection loop
        while (!(std::cin >> upperBound))
        {
            //TODO, add a guard against max int size
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Please enter an integer >= 2 for the upper bound: ";
        }
    }
    else
    {
        upperBound = std::stoi(std::string(argv[1]));
    }
    std::vector<int> vec;
    vec = findPrimes(upperBound);
    for(int i : vec){
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    return 0;
}