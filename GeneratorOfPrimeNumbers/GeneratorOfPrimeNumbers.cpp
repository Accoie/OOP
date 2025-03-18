#include <iostream>
#include <cstdlib> 
#include "Windows.h"
#include "GeneratePrimeNumbersSet.h"
#include <chrono>

const int MIN_UPPERBOUND = 1;
const int MAX_UPPERBOUND = 100000000;

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    // вынести ф функции
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <upperBound>" << std::endl;
        return 1;
    }
    // upperbound вынести в функцию и протеситть
    int upperBound = std::atoi(argv[1]);

    if (upperBound < MIN_UPPERBOUND || upperBound > MAX_UPPERBOUND) {
        std::cerr << "Верхняя граница должна быть в диапазоне от 1 до 100000000" << std::endl;
        return 1;
    }

    std::set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);

    std::cout << "Найдено простых чисел: " << primeNumbersSet.size() << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Execution time: " << elapsed.count() << " seconds\n";
    return 0;
}