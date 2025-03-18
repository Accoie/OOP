#include "ToLowerCase.h"

std::string ToLowerCase(std::string str)
{
    std::string result = {};
    std::transform(str.begin(), str.end(), std::back_inserter(result), [](char ch) {return std::tolower(ch); });
    return result;
}