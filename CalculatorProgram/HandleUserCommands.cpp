#include "HandleUserCommands.h"
#include "HandleVar.h"
#include "HandleLet.h"
#include "HandleFn.h"
#include "ParseLine.h"

namespace Commands {
    const std::string VAR = "var";
    const std::string LET = "let";
    const std::string FUNCTION = "fn";
    const std::string PRINT = "print";
    const std::string PRINT_VAR = "printvars";
    const std::string PRINT_FUNCTIONS = "printfns";
}

const int MAX_TOKENS_SIZE = 6;

void HandleUserCommands(Calculator& calc, std::string line, std::ostream &out)
{
    std::vector<std::string> tokens = {};
    ParseLine(line, tokens);

    
    try {
        if (tokens.empty())
        {
            throw std::invalid_argument("Empty input");
        }
        std::string command = tokens[0];
        if (tokens.empty() || tokens.size() > MAX_TOKENS_SIZE)
        {
            throw std::invalid_argument("Invalid syntax");
        }
        if (command == Commands::VAR)
        {
            HandleVar(calc, tokens);
        }
        else if (command == Commands::LET)
        {
            HandleLet(calc, tokens);
        } 
        else if (command == Commands::FUNCTION)
        {
            HandleFn(calc, tokens);
        } 
        else if (command == Commands::PRINT)
        { 
            calc.PrintValue(tokens, out);
        } 
        else if (command == Commands::PRINT_VAR)
        {
            calc.PrintVariables(out);
        } 
        else if (command == Commands::PRINT_FUNCTIONS)
        {
            calc.PrintFunctions(out);
        } 
        else
        {
            throw std::invalid_argument("Unknown command");
        }
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    
}