#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>

void PrintSortedNumbers(std::vector<double> sortedNumbers)
{
    for (auto i : sortedNumbers)
    {
        std::cout << std::fixed << std::setprecision(3) << i << " ";
    }
}

std::vector<double> SortNumbers(std::vector<double> numbers)
{
    std::sort(numbers.begin(), numbers.end(), [](double a, double b) {  return a < b; });
    return numbers;
}

bool ReadNumbers(std::vector<double> &numbers) 
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    double number;
    while (iss >> number) 
    {
        numbers.push_back(number);
    }
    if (iss.fail() && !iss.eof())
    {
        return false;
    }
    return true;
}
double AccumulatePositive(double acc, double num)
{
    return num > 0 ? acc + num : acc;
}
bool IsPositive(double num)
{
    return num > 0;
}
// делать одну строку отступа меджду функциями, поменять название 
std::vector<double> ProcessNumbers(std::vector<double> numbers)
{
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0, AccumulatePositive);
    double count = std::count_if(numbers.begin(), numbers.end(), IsPositive);
    if (count <= 0)
    {
        return numbers;
    }
    double average = sum / count;
    std::vector<double> result = {};
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(result), [average](double num) { return num + average; });
    
    return result;
}
int main()
{
    std::vector<double> numbers = {};
    if (!ReadNumbers(numbers))
    {
        std::cout << "ERROR\n";
        return 0;
    }
    std::vector<double> processedNumbers = ProcessNumbers(numbers);
    std::vector<double> sortedNumbers = SortNumbers(processedNumbers);
    PrintSortedNumbers(sortedNumbers);
}
