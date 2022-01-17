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
   
    do 
    {
        std::cout << "Enter a whole number lower bound to evaluate all prime numbers witin the range: ";
        std::cin >> lowerBound;
        std::cout << std::endl;
        //sets fail bool, and clears input buffer if failure accord
        clear_buffer(&fail);
        if (lowerBound < 0)
            fail = true;
    } while (fail);
    do {
        std::cout << "Enter an whole number upper bound( i.e. greater than or equal to lower bound): ";
        std::cin >> upperBound;
        //sets fail bool, and clears input buffer if failure accord
        clear_buffer(&fail);
        if ( upperBound < lowerBound)
            fail = true;
    } while (fail);
    
    if (upperBound > 2)
    {
        midBound = (upperBound / 2);
        if (midBound < lowerBound)
            midBound = lowerBound + 1;
        std::thread t1(Prime, lowerBound, midBound);
        // offset midbound to avoid rerunning the same number
        std::thread t2(Prime, midBound + 1, upperBound);
        t1.join();
        t2.join();
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


void  Prime(int num, int upperBound)
{
    for (int index = num; index <= upperBound; index++)
    {
        if (isPrime(index))
        {
            conch.lock();
            vec.push_back(index);
            conch.unlock();
        }
    }
   
}
bool isPrime(int num) {
    if (num <= 1 || (num % 2 == 0 && num != 2)) //even and not natural number check
        return false;

    for (int index = 3; index <= sqrt(num); index += 2) { //sqrt(num) to cut down on exe time
        if (num % index == 0)
            return false;
    }
    return true;
}
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