#include "catch_amalgamated.hpp"
#include "primes.hpp"

TEST_CASE("findPrimes test"){
    CHECK(findPrimes(10) ==  std::vector<int>{2,3,5,7});
    //should fail
    CHECK(findPrimes(10) == std::vector<int>{4,6,8,9});
}