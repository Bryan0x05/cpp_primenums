#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <algorithm>
#include <vector>

std::mutex conch;
// global vector for threads to store prime
std::vector<int> vec;
// Checks if the number is prime
bool isPrime(int num);
// iteraties through the range specified by the bounds calling isPrime
void Prime(int num, int upperBound);
//sets failure flag, and clears input buffer if flag is set
void clear_buffer(bool* fail);

int main(int argc, char** argv)
{
    int upperBound = 0, midBound = 0, lowerBound = 0;
    bool fail = false;
    std::string test;
    // lower bound input safe guard loop
    do 
    {
        std::cout << "Enter a counting number to serve as a lower bound: ";
        std::cin >> lowerBound;
        std::cout << std::endl;
        // sets fail bool, and clears input buffer if failure occurred
        clear_buffer(&fail);
        if (lowerBound < 0)
            fail = true;
    } while (fail);
    
    // upper bound input safe guard loop
    do {
        std::cout << "Enter a counting number to serve as an upper bound that is greater than the lower bound: ";
        std::cin >> upperBound;
        //sets fail bool, and clears input buffer if failure accord
        clear_buffer(&fail);
        if ( upperBound < lowerBound)
            fail = true;
    } while(fail);
    //multi-thread logic  
    if(upperBound >= 100)
    {
        std::vector<std::thread*> threadVec;
        while(upperBound >= 100){
            midBound = upperBound-100;
            std::thread *t = new std::thread(Prime, midBound, upperBound);
            threadVec.emplace_back(t);
            //offset by 1 to prevent overlapping calculations
            upperBound -= 101; 
        }
        if(upperBound > 0){
            std::thread* t = new std::thread(Prime, 0, upperBound);
            threadVec.emplace_back(t);
        }
        //wait for all threads to complete
        for(auto thread : threadVec){
            thread->join();
            delete thread;
        }
    }
    else
        Prime(0, upperBound);

    std::sort(vec.begin(), vec.end());
    std::cout << "---------------\nprimes: ";
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ", ";
    std::cout << std::endl;
    
    return 0;
}

void Prime(int num, int upperBound)
{
    for (int index = num; index <= upperBound; index++)
    {
        if (isPrime(index))
        {
            //using mutex to prevent race conditions w/ multi-threading
            conch.lock();
            vec.push_back(index);
            conch.unlock();
        }
    }
   
}
//checks if the given number is prime
//Note this is ineffecient, for each number, it has to check all the prime numbers that came before it to
//validate that it is prime. However, this wouldn't be required with a static lower bound, could also do caching
//to reduce calucations.
bool isPrime(int num) {
    if (num <= 1 || (num % 2 == 0 && num != 2)) //even and not natural number check
        return false;

    for (int index = 3; index <= sqrt(num); index += 2) { //sqrt(num) to cut down on exe time
        if (num % index == 0)
            return false;
    }
    return true;
}
//clears input buffer
void clear_buffer(bool* fail )
{
    if (std::cin.fail())
    {
        *fail = true;
        // clears error flags to allow ignore to be used
        std::cin.clear();
        // ignore will maxium amount of characters until eof, function failure or new line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
        *fail = false;
}