#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <stdexcept>

bool IsValidChar(char c, int radix) 
{
    if (std::isdigit(c))
    {
        return (c - '0') < radix;
    }
    if (std::isupper(c))
    {
        return (c - 'A' + 10) < radix;
    }
    return false;
}

int CharToDigit(char c)
{
    return std::isdigit(c) ? c - '0' : c - 'A' + 10; // 0 A и - в константы
}

char DigitToChar(int digit) 
{
    return digit < 10 ? '0' + digit : 'A' + (digit - 10);
}

int StringToInt(const std::string &str, int radix, bool &wasError)
{
    wasError = false;
    if (radix < 2 || radix > 36 || str.empty()) 
    {
        wasError = true;
        return 0;
    }

    int result = 0;
    bool isNegative = (str[0] == '-');
    size_t start = isNegative ? 1 : 0;

    for (size_t i = start; i < str.size(); ++i) 
    {
        char c = std::toupper(str[i]);
        if (!IsValidChar(c, radix)) 
        {
            wasError = true;
            return 0;
        }

        int digit = CharToDigit(c);
        if ((result > (std::numeric_limits<int>::max() - digit) / radix) || (result < (std::numeric_limits<int>::min() - digit) / radix))// проверка на min переоплнение 
        {
            wasError = true;
            return 0;
        }

        result = result * radix + digit;
    }

    return isNegative ? -result : result;
}

std::string IntToString(int n, int radix, bool &wasError)
{
    wasError = false;
    if (radix < 2 || radix > 36) 
    {
        wasError = true;
        return "";
    }

    if (n == 0)
    {
        return "0";
    }

    bool isNegative = (n < 0);
    unsigned int value = isNegative ? -n : n;

    std::string result;
    while (value > 0)
    {
        result = DigitToChar(value % radix) + result;
        value /= radix;
    }

    if (isNegative) 
    {
        result = "-" + result;
    }
    return result;
}

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        std::cerr << "Usage: radix.exe <source notation> <destination notation> <value>\n";
        return 1;
    }

    int sourceBase, destBase;// в проедуру
    try 
    {
        sourceBase = std::stoi(argv[1]);
        destBase = std::stoi(argv[2]);
    }
    catch (...) 
    {
        std::cerr << "Invalid base values.\n";
        return 1;
    }//

    bool wasError = false;
    int number = StringToInt(argv[3], sourceBase, wasError);
    if (wasError) 
    {
        std::cerr << "Invalid number representation.\n";
        return 1;
    }

    std::string result = IntToString(number, destBase, wasError);
    if (wasError) 
    {
        std::cerr << "Conversion error.\n";
        return 1;
    }

    std::cout << result << "\n";
    return 0;
}
//2147483647
//-2147483648