#include "GeneratePrimeNumbersSet.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound) {
    std::set<int> primes = {};
    if (upperBound < 2) {
        return primes;
    }

    std::vector<bool> isPrime(upperBound + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= std::sqrt(upperBound); ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= upperBound; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound; ++i) {
        if (isPrime[i]) {
            primes.insert(i);
        }
    }

    return primes;
}
