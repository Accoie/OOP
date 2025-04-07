#include "Calculator.h"
#include "Function.h"
#include "Variable.h"
#include <iostream>

void Calculator::PrintValue(const std::vector<std::string>& tokens)
{
    if (tokens.size() != 2)
    {
        std::cout << "Unknown command" << std::endl;
        return;
    }

    std::string id = tokens[1];
    auto it = FindInVariables(id);
    if (it != GetVariables().end())
    {
        double value = (*it)->GetValue();
        if (std::isnan(value))
        {
            std::cout << "nan" << std::endl;
        }
        else
        {
            std::cout << std::fixed << std::setprecision(2) << value << std::endl;
        }
        return;
    }

    auto functionIt = FindInFunctions(id);
    if (functionIt != GetFunctions().end())
    {
        double value = (*functionIt)->GetValue();
        if (std::isnan(value))
        {
            std::cout << "nan" << std::endl;
        }
        else
        {
            std::cout << std::fixed << std::setprecision(2) << value << std::endl;
        }
        return;
    }

    std::cout << "Identifier not found: " << id << std::endl;
}
void Calculator::PrintVariables()
{
    auto vars = m_variables;
    if (vars.empty()) return;

    std::sort(vars.begin(), vars.end(),
        [](const auto& a, const auto& b) { return a->GetName() < b->GetName(); });

    for (const auto& var : vars)
    {
        double value = var->GetValue();
        std::cout << var->GetName() << ":";
        if (std::isnan(value)) 
        {
            std::cout << "nan";
        } 
        else
        {
            std::cout << std::fixed << std::setprecision(2) << value;
        }
        std::cout << std::endl;
    }
}
void Calculator::PrintFunctions()
{
    auto fns = m_functions;
    if (fns.empty()) return;

    std::sort(fns.begin(), fns.end(),
        [](const auto& a, const auto& b) { return a->GetName() < b->GetName(); });

    for (const auto& fn : fns)
    {
        double value = fn->GetValue();
        std::cout << fn->GetName() << ":";
        if (std::isnan(value)) {
            std::cout << "nan";
        } 
        else
        {
            std::cout << std::fixed << std::setprecision(2) << value;
        }
        std::cout << std::endl;
    }
}
const VariablesType &Calculator::GetVariables() const {
    return m_variables;
}
const FunctionsType &Calculator::GetFunctions() const {
    return m_functions;
}
FunctionsType::iterator Calculator::FindInFunctions(std::string name) 
{
    return std::find_if(m_functions.begin(), m_functions.end(), [name](std::shared_ptr<Function> f) {return f->GetName() == name; });
};

VariablesType::iterator Calculator::FindInVariables(std::string name) 
{
    return std::find_if(m_variables.begin(), m_variables.end(), [name](std::shared_ptr<Variable> f) {return f->GetName() == name; });
};

std::optional<ArgumentType> Calculator::FindArgument(std::string name)
{
    auto funcIt = FindInFunctions(name);
    auto varIt = FindInVariables(name);
    if (funcIt != m_functions.end())
    {
        return *funcIt;
    } 
    else if (varIt != m_variables.end())
    {
        return *varIt;
    }  
    else
    {
        return std::nullopt;
    }
};

bool Calculator::CheckExistOperation(std::string op)
{
    if (StringToOperation(op).has_value())
    {
        return true;
    }
    else
    {
        std::cout << "Operation doesn't exist \n";
        return false;
    }
};

bool Calculator::CheckExist(std::string name)
{
    return FindInFunctions(name) != m_functions.end() || FindInVariables(name) != m_variables.end();
};

bool Calculator::CheckFunction(std::string name, 
    std::string argFirstName, 
    std::optional<std::string> argSecondName,
    std::optional<std::string> op)
{
    if (CheckExist(name))
    {
        std::cout << "Name already exists\n";
        return false;
    }
    if (argSecondName.has_value() && op.has_value() && argSecondName.value() != "" && op.value() != "")
    {
        return CheckExist(argFirstName) && CheckExist(argSecondName.value()) && CheckExistOperation(op.value());
    }
    else if (!argSecondName.has_value() && !op.has_value())
    {
        return CheckExist(argFirstName);
    }
    else
    {
        std::cout << "Uncorrect syntax\n";
        return false;
    }
    
};


std::optional<std::shared_ptr<Function>> Calculator::MakeFunction(std::string name,
    std::string argFirstName,
    std::optional<std::string> argSecondName,
    std::optional<std::string> op)
{
    std::optional<ArgumentType> argFirst = FindArgument(argFirstName);
    if (argFirst.has_value())
    {
        std::optional<ArgumentType> argSecond = std::nullopt;
        std::optional<Operation> operation = std::nullopt;

        if (argSecondName.has_value() && op.has_value())
        {
            argSecond = FindArgument(argSecondName.value());
            operation = StringToOperation(op.value()).value();
            if (!argSecond.has_value() || !argSecondName.has_value()) 
            {
                std::cout << "Error was occured with second argument or with operation\n";
                return std::nullopt;
            };
        }
        std::shared_ptr<Function> func = Function::CreateFunction(name, argFirst.value(), argSecond, operation);
        return func;
    }
    else
    {
        std::cout << "Error was occured with first argument\n";
        return std::nullopt;
    }
};
bool Calculator::AddToFunctions(std::string name,
    std::string argFirstName, 
    std::optional<std::string> argSecondName,
    std::optional<std::string> op)
{
    if (CheckFunction(name, argFirstName, argSecondName, op))
    {
        auto func = MakeFunction(name, argFirstName, argSecondName, op);
        if (func.has_value())
        {
            m_functions.push_back(func.value());
            return true;
        }
        else 
        {
            return false;
        }
    }
    else
    {
        return false;
    }

};
Calculator::StatusOfCheckVariable Calculator::CheckVariable(std::string name, std::optional<std::string> argName, std::optional<double> value)
{
    if (name == "" || argName == "")
    {
        std::cout << "Incorrect syntax: empty string\n";
        return notPassed;
    }
    if ((argName.has_value() && CheckExist(argName.value()) && !value.has_value()) || (!argName.has_value() && value.has_value()))
    {
        return CheckExist(name) ? changeValue : defineVar;
    }
    else if (argName.has_value() && !CheckExist(argName.value()))
    {
        std::cout << "Argument's name doesn't exist\n";
        return notPassed;
    }
    else
    {
        std::cout << "Incorrect syntax\n";
        return notPassed;
    }
}

std::optional<std::shared_ptr<Variable>> Calculator::MakeVariable(std::string name, std::optional<std::string> argName, std::optional<double> value)
{
    switch (CheckVariable(name, argName, value))
    {
        case notPassed: {
            return std::nullopt;
        }
        case defineVar: {
            std::optional<ArgumentType> arg = argName.has_value() ? FindArgument(argName.value()) : std::nullopt;
            return Variable::CreateVariable(name, arg, value);
        }
        case changeValue: {
                auto it = FindInVariables(name);
                if (it != m_variables.end()) {
                    std::optional<ArgumentType> arg = argName.has_value() ? FindArgument(argName.value()) : std::nullopt;
                    std::shared_ptr<Variable>& var = *it;
                    arg != std::nullopt ? var->ChangeArgument(arg.value()) : var->ChangeValue(value.value_or(NAN));
                }
            
            return std::nullopt;
        }
    }
    return std::nullopt;
};

bool Calculator::AddToVariables(std::string name, std::optional<std::string> argName, std::optional<double> value)
{
    std::optional<std::shared_ptr<Variable>> var = MakeVariable(name, argName, value);
    if (var.has_value())
    {
        m_variables.push_back(var.value());
        return true;
    }
    else
    {
        return false;
    }
};