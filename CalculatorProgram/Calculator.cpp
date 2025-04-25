#include "Calculator.h"
#include "Function.h"
#include "Variable.h"
#include "Argument.h"
#include <iostream>
#include <queue>

void PrintValueInOutput(double value, std::ostream& out)
{
    if (std::isnan(value))
    {
        out << "nan\n";
    } 
    else
    {
        out << std::fixed << std::setprecision(2) << value << "\n";
    }
}

void Calculator::PrintValue(const std::vector<std::string>& tokens, std::ostream& out)
{
    if (tokens.size() != 2)
    {
        throw std::invalid_argument("Unknown command");
        return;
    }

    std::string id = tokens[1];
    auto it = FindInVariables(id);
    if (it != GetVariables().end())
    {
        double value = (*it)->GetValue();
        PrintValueInOutput(value, out);
        return;
    }

    auto functionIt = FindInFunctions(id);
    if (functionIt != GetFunctions().end())
    {
        double value = (*functionIt)->GetValue();
        PrintValueInOutput(value, out);
        return;
    }
    throw std::invalid_argument("Identifier not found");
}
void Calculator::PrintVariables(std::ostream& out)
{
    auto vars = m_variables;
    if (vars.empty())
    {
        return;
    }
    std::sort(vars.begin(), vars.end(),
        [](const auto& a, const auto& b) { return a->GetName() < b->GetName(); });

    for (const auto& var : vars)
    {
        double value = var->GetValue();
        out << var->GetName() << ":";
        PrintValueInOutput(value, out);
        
    }
}
void Calculator::PrintFunctions(std::ostream& out)
{
    auto functions = m_functions;
    if (functions.empty())
    {
        return;
    }

    std::sort(functions.begin(), functions.end(),
        [](const auto& a, const auto& b) { return a->GetName() < b->GetName(); });

    for (const auto& func : functions)
    {
        double value = func->GetValue();
        out << func->GetName() << ":";
        PrintValueInOutput(value, out);
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
}

VariablesType::iterator Calculator::FindInVariables(std::string name) 
{
    return std::find_if(m_variables.begin(), m_variables.end(), [name](std::shared_ptr<Variable> f) {return f->GetName() == name; });
}
// сделать через map
std::optional<ArgumentType> Calculator::FindArgument(std::string name)
{
    auto funcIt = FindInFunctions(name);
    auto varIt = FindInVariables(name);
    if (funcIt != m_functions.end())
    {
        return *funcIt;
    } 
    if (varIt != m_variables.end())
    {
        return *varIt;
    }  
    return std::nullopt;
}

bool Calculator::CheckExistOperation(std::string op)
{
    if (!StringToOperation(op).has_value())
    {
        std::cout << "Operation doesn't exist \n";
        return false;
    }
    return true;
}

bool Calculator::CheckArgumentExist(std::string name)
{
    return FindInFunctions(name) != m_functions.end() || FindInVariables(name) != m_variables.end();
};

StatusOfValidateFunction Calculator::ValidateFunction(std::string name, 
    std::string argFirstName, 
    std::optional<std::string> argSecondName,
    std::optional<std::string> operation)
{
    if (CheckArgumentExist(name))
    {
        throw std::invalid_argument("Function already exists");
    }
    if (!CheckArgumentExist(argFirstName))
    {
        throw std::invalid_argument("First argument doesn't exist");
    }
    if (name == "" || argFirstName == "") 
    {
        throw std::invalid_argument("Empty string in name of function or argument");
    }
    if (argSecondName.has_value() && operation.has_value())
    {
        if (argSecondName.value() == "" || operation.value() == "")
        {
            throw std::invalid_argument("Empty string in second argument or operation");
        }
        if (!CheckArgumentExist(argSecondName.value()))
        {
            throw std::invalid_argument("Second argument doesn't exist");
        }
        if (!CheckExistOperation(operation.value()))
        {
            throw std::invalid_argument("Operation doesn't exist");
        }
        return functionTwoArguments;
    }
    if (!argSecondName.has_value() && !operation.has_value())
    {
        return functionOneArgument;
    }    
    throw std::invalid_argument("Invalid parametres");
}

std::shared_ptr<Function> Calculator::MakeFunction(std::string name,
    std::string argFirstName,
    std::optional<std::string> argSecondName,
    std::optional<std::string> op)
{
    try {
        switch (ValidateFunction(name, argFirstName, argSecondName, op))
        {
            case functionOneArgument :
            {
                ArgumentType argFirst = FindArgument(argFirstName).value();
                return Function::CreateFunction(name, argFirst);
            }
            case functionTwoArguments : 
            {
                ArgumentType argFirst = FindArgument(argFirstName).value();
                ArgumentType argSecond = FindArgument(argSecondName.value()).value();
                Operation operation = StringToOperation(op.value()).value();
                return Function::CreateFunction(name, argFirst, argSecond, operation);
            }
        }
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    return nullptr;
}

bool Calculator::AddToFunctions(std::string name,
    std::string argFirstName, 
    std::optional<std::string> argSecondName,
    std::optional<std::string> op)
{
    auto func = MakeFunction(name, argFirstName, argSecondName, op);
    if (!func)
    {
        return false;
    }
    m_functions.push_back(func);
    return true;
} 

StatusOfValidateVariable Calculator::ValidateVariable(std::string name, std::optional<std::string> argName, std::optional<double> value)
{
    if (name == "" || argName == "")
    {
        throw std::invalid_argument("Incorrect syntax: empty string");
    }
    if (argName.has_value())
    {
        if (!CheckArgumentExist(argName.value()))
        {
            throw std::invalid_argument("Argument's name doesn't exist");
        }
    }
    else
    {
        if (!value.has_value())
        {
            if (CheckArgumentExist(name))
            {
                throw std::invalid_argument("Variable is already exist");
            }
            return defineVar;
        }
    }
    return CheckArgumentExist(name) ? changeValue : defineVar;
}

void Calculator::UpdateFunctions(std::queue<std::shared_ptr<Function>> &updatingFunctions, std::shared_ptr<Function>& updatedFunction)
{
    // [s2]
    for (auto& function : m_functions)
    {
        ArgumentType firstArgument = function->GetFirstArgument();
        std::optional<ArgumentType> secondArgument = function->GetSecondArgument();
        std::string name = updatedFunction->GetName();
        if (GetArgumentName(firstArgument) == name || (secondArgument.has_value() && GetArgumentName(secondArgument.value()) == name))
        {
            updatingFunctions.push(function);
        }
    }
    
    // [s2]
    if (!updatingFunctions.empty())
    {
        updatedFunction = updatingFunctions.front();
        updatedFunction->ActualizeValue();
        updatingFunctions.pop();
        UpdateFunctions(updatingFunctions, updatedFunction);
    }
};
void Calculator::ActualizeFunctions(std::shared_ptr<Variable> &updatedVariable)
{
    std::queue<std::shared_ptr<Function>> updatableFunctions;
    for (auto& function : m_functions)
    {
        ArgumentType firstArgument = function->GetFirstArgument();
        std::optional<ArgumentType> secondArgument = function->GetSecondArgument();
        std::string name = updatedVariable->GetName();
        if (GetArgumentName(firstArgument) == name || (secondArgument.has_value() && GetArgumentName(secondArgument.value()) == name))
        {
            updatableFunctions.push(function);
        }
    }

    // [s1, s2]
    if (!updatableFunctions.empty())
    {
        std::shared_ptr<Function> updatedFunction = updatableFunctions.front();
        updatedFunction->ActualizeValue();
        updatableFunctions.pop();
        // [s2]
        UpdateFunctions(updatableFunctions, updatedFunction);
    }
};
std::shared_ptr<Variable> Calculator::MakeVariable(std::string name, std::optional<std::string> argName, std::optional<double> value)
{
    try {
        switch (ValidateVariable(name, argName, value))
        {
            case defineVar: {
                std::optional<ArgumentType> arg = argName.has_value() ? FindArgument(argName.value()) : std::nullopt;
                return Variable::CreateVariable(name, arg, value);
            }
            case changeValue: {
                auto it = FindInVariables(name);
                std::optional<ArgumentType> arg = argName.has_value() ? FindArgument(argName.value()) : std::nullopt;
                std::shared_ptr<Variable>& var = *it;
                arg != std::nullopt ? var->ChangeArgument(arg.value()) : var->ChangeValue(value.value());
                std::shared_ptr<Variable> newVar = *it;
                ActualizeFunctions(newVar);

                return nullptr;
            }
        }
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

    return nullptr;
}

bool Calculator::AddToVariables(std::string name, std::optional<std::string> argName, std::optional<double> value)
{
    
    std::shared_ptr<Variable> var = MakeVariable(name, argName, value);
    if (!var)
    {
        return false;
    }
    m_variables.push_back(var);
    return true;
}