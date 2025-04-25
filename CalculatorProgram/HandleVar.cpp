#include "HandleVar.h"

void HandleVar(Calculator& calc, const std::vector<std::string>& tokens)
{
    if (tokens.size() != 2 || !IsValidIdentifier(tokens[1]))
    {
        throw std::invalid_argument("Invalid var command");
        
        return;
    }

    if (!calc.AddToVariables(tokens[1]))
    {
        throw std::invalid_argument("Variable already exists");
    }
}