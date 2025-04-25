#include "ParseLine.h"

void ParseLine(const std::string& line, std::vector<std::string> &tokens)
{
    std::istringstream iss(line);
    std::string token;

    while (iss >> token) 
    {
        std::size_t posOfFoundOperation = std::string::npos;
        if (!tokens.empty())
        {
            posOfFoundOperation = tokens.at(0) == "let" ? token.find(Operations::EQUAL) : token.find_first_of(Operations::OPERATIONS_STRING);
        }
        if (posOfFoundOperation != std::string::npos && token.size() > 1)
        {
            std::string beforeOperation = token.substr(0, posOfFoundOperation);
            std::string operation = token.substr(posOfFoundOperation, 1);
            std::string afterOperation = token.substr(posOfFoundOperation + 1);

            if (!beforeOperation.empty())
            {
                tokens.push_back(beforeOperation);
            }
            tokens.push_back(operation);
            if (!afterOperation.empty())
            {
                ParseLine(afterOperation, tokens);
            }
        }
        else
        {
            tokens.push_back(token);
        }
    }
}