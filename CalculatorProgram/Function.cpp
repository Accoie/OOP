#include "Function.h"
#include "Variable.h"
#include <iostream>
#include <cmath>

Function::Function(
    std::string name,
    ArgumentType argumentFirst,
    std::optional<ArgumentType> argumentSecond,
    std::optional<Operation> operation,
    double value)
    : m_name(std::move(name)),
    m_argumentFirst(std::move(argumentFirst)),
    m_argumentSecond(std::move(argumentSecond)),
    m_operation(std::move(operation)),
    m_value(value)
{
}

std::string Function::GetName() const { return m_name; }
const ArgumentType& Function::GetFirstArgument() const { return m_argumentFirst; }
const std::optional<ArgumentType>& Function::GetSecondArgument() const { return m_argumentSecond; }
const std::optional<Operation>& Function::GetOperation() const { return m_operation; }
double Function::GetValue() const { return m_value; }

void Function::ActualizeValue()
{
    m_value = CalculateFunctionValue(m_argumentFirst, m_argumentSecond, m_operation);
};
double Function::CalculateByOperation(
    const ArgumentType& argumentFirst,
    const std::optional<ArgumentType>& argumentSecond,
    const std::optional<Operation>& operation
)
{
    std::optional<double> argumentFirstValue = GetArgumentValue(argumentFirst);
    std::optional<double> argumentSecondValue = GetArgumentValue(argumentSecond.value());
    
    if (argumentFirstValue.has_value() && argumentSecondValue.has_value())
    {
        double value = -INFINITY;
        switch (operation.value())
        {
        case Operation::Add:
        {
            value = argumentFirstValue.value() + argumentSecondValue.value();
            break;
        }
        case Operation::Subtract:
        {
            value = argumentFirstValue.value() - argumentSecondValue.value();
            break;
        }
        case Operation::Multiply:
        {

            value = argumentFirstValue.value() * argumentSecondValue.value();
            break;
        }

        case Operation::Divide:
        {
            if (argumentFirstValue.value() != NAN && argumentSecondValue.value() != NAN && argumentSecondValue.value() != 0)
            {
                value = argumentFirstValue.value() / argumentSecondValue.value();
            } 
            else
            {
                value = NAN;
            }
            break;
        }
        }
        if (value == INFINITY)
        {
            throw std::out_of_range("Out of range");
        }
        return value;
    } 
    else
    {
        throw std::invalid_argument("Failed to calculate function value : argument don't have value");
    }
    
}


double Function::CalculateFunctionValue(
    const ArgumentType& argumentFirst,
    const std::optional<ArgumentType>& argumentSecond,
    const std::optional<Operation>& operation)
{

    if (!argumentSecond.has_value() && !operation.has_value())
    {
        return GetArgumentValue(argumentFirst);
    } 
    return CalculateByOperation(argumentFirst, argumentSecond, operation);
}

std::shared_ptr<Function> Function::CreateFunction(
    std::string name,
    ArgumentType argumentFirst,
    std::optional<ArgumentType> argumentSecond,
    std::optional<Operation> operation
)
{
    try 
    {
        double value = CalculateFunctionValue(argumentFirst, argumentSecond, operation);
        return std::make_shared<Function>(Function(name,
            std::move(argumentFirst),
            std::move(argumentSecond),
            std::move(operation),
            value));
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    return nullptr;
};