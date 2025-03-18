#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../GeneratePrimeNumbersSet.h"
#include <set>
TEST_CASE("GeneratePrimeNumbersSet - верхн€€ граница меньше 2") {
    std::set<int> expected = {};
    CHECK(GeneratePrimeNumbersSet(1) == expected);
    CHECK(GeneratePrimeNumbersSet(0) == expected);
    CHECK(GeneratePrimeNumbersSet(-10) == expected);
}

TEST_CASE("GeneratePrimeNumbersSet - верхн€€ граница 2") {
    std::set<int> expected = { 2 };
    CHECK(GeneratePrimeNumbersSet(2) == expected);
}

TEST_CASE("GeneratePrimeNumbersSet - верхн€€ граница 10") {
    std::set<int> expected = { 2, 3, 5, 7 };
    CHECK(GeneratePrimeNumbersSet(10) == expected);
}

TEST_CASE("GeneratePrimeNumbersSet - верхн€€ граница 30") {
    std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    CHECK(GeneratePrimeNumbersSet(30) == expected);
}

TEST_CASE("GeneratePrimeNumbersSet - верхн€€ граница 100") {
    std::set<int> expected = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    CHECK(GeneratePrimeNumbersSet(100) == expected);
}

TEST_CASE("GeneratePrimeNumbersSet - верхн€€ граница 100000000") {
    std::set<int> primes = GeneratePrimeNumbersSet(100000000);
    CHECK(primes.size() == 5761455);
}