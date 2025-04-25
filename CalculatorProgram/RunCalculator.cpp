#include "RunCalculator.h"
#include "HandleUserCommands.h"
#include "Calculator.h"
#include <iostream>

void RunCalculator(std::ostream& out)
{
    Calculator calc;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            continue;
        }
        else if (line == "...")
        {
            break;
        }
        HandleUserCommands(calc, line, out);
    }
}