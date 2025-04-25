#include "Argument.h"
#include "Variable.h"
#include "Function.h"
#include <iostream>

double GetArgumentValue(const ArgumentType& argument) 
{
    return std::visit([](auto arg)->double
        {
            if (!arg)
            {
                throw std::invalid_argument("Failed to get value: nullptr");
            }
            if constexpr (std::is_same_v<decltype(arg), std::shared_ptr<Function>>)
            {
                return arg->Function::GetValue();
            } 
            else if constexpr (std::is_same_v<decltype(arg), std::shared_ptr<Variable>>)
            {
                return arg->Variable::GetValue();
            }

        }, argument);
}
std::string GetArgumentName(const ArgumentType& argument)
{
    return std::visit([](auto arg)->std::string
        {
            if (!arg)
            {
                throw std::invalid_argument("Failed to get value: nullptr");
            }
            if constexpr (std::is_same_v<decltype(arg), std::shared_ptr<Function>>)
            {
                return arg->Function::GetName();
            } 
            else if constexpr (std::is_same_v<decltype(arg), std::shared_ptr<Variable>>)
            {
                return arg->Variable::GetName();
            }

        }, argument);
}