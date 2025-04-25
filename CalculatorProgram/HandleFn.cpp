#include "HandleFn.h"

void HandleFn(Calculator& calc, const std::vector<std::string>& tokens)
{
    if (tokens.size() < 4 || tokens[2] != "=")
    {
        throw std::invalid_argument("Invalid fn command");
    }

    std::string fnName = tokens[1];
    if (!IsValidIdentifier(fnName))
    {
        throw std::invalid_argument("Invalid function name");
    }

    if (tokens.size() == 4)
    {
        if (calc.AddToFunctions(fnName, tokens[3]))
        {
            return;
        }
        throw std::invalid_argument("Failed to create function");
        return;
    }

    if (tokens.size() == 6)
    {
        std::string op = tokens[4];
        if (op.size() != 1 || std::string("+-*/").find(op) == std::string::npos)
        {
            throw std::invalid_argument("Invalid operator");
        }

        if (calc.AddToFunctions(fnName, tokens[3], tokens[5], op))
        {
            return;
        }
        throw std::invalid_argument("Failed to create function");
    }
}
