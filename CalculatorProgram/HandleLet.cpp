#include "HandleLet.h"
#include <sstream>

const double MAX_DOUBLE = std::numeric_limits<double>::max();
const double MIN_DOUBLE = std::numeric_limits<double>::min();

void HandleLet(Calculator& calc, const std::vector<std::string>& tokens)
{
    if (tokens.size() < 4 || tokens[2] != "=") {
        throw std::invalid_argument("Unknown command");
    }

    std::string varName = tokens[1];

    if (!IsValidIdentifier(varName))
    {
        throw std::invalid_argument("Invalid identifier");
    }

    if (tokens.size() == 4 && IsValidIdentifier(tokens[3]))
    {
        calc.AddToVariables(varName, tokens[3]);
        return;
    }

    try {
        size_t pos = 0;
        double value = std::stod(tokens[3], &pos);
        if (value == MAX_DOUBLE)
        {
            std::cout << "Maximum\n";
        }
        else if (value == MIN_DOUBLE)
        {
            std::cout << "Minimum\n";
        }
 
        std::ostringstream ss;
        ss << value;
        if (value > MAX_DOUBLE || (value < MIN_DOUBLE && value != 0)) {
            throw std::invalid_argument("Value is too large or too small");
        }
        
        calc.AddToVariables(varName, std::nullopt, value);
        return;
    }
    catch (std::invalid_argument e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::out_of_range e)
    {
        std::cout << "Value is too large or too small" << std::endl;
    }
    std::cout << "Invalid right side in let command" << std::endl;
}