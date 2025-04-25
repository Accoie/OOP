#pragma once


#include <memory>
#include <optional>
#include <variant>
#include <string>
#include <utility>
#include "Argument.h"
#include "Operation.h"

class Function
{
public:

    static std::shared_ptr<Function> CreateFunction(
        std::string name,
        ArgumentType argumentFirst,
        std::optional<ArgumentType> argumentSecond = std::nullopt,
        std::optional<Operation> operation = std::nullopt
    );

    std::string GetName() const;
    const ArgumentType& GetFirstArgument() const;
    const std::optional<ArgumentType>& GetSecondArgument() const;
    const std::optional<Operation>& GetOperation() const;
    double GetValue() const;
    void ActualizeValue();
   
private:
    Function(
        std::string name,
        ArgumentType argumentFirst,
        std::optional<ArgumentType> argumentSecond,
        std::optional<Operation> operation,
        double value
    );

    static double CalculateByOperation(
        const ArgumentType& argumentFirst,
        const std::optional<ArgumentType>& argumentSecond,
        const std::optional<Operation>& operation
    );

    static double CalculateFunctionValue(
        const ArgumentType& argumentFirst,
        const std::optional<ArgumentType>& argumentSecond,
        const std::optional<Operation>& operation
    );

    std::string m_name;
    ArgumentType m_argumentFirst;
    std::optional<ArgumentType> m_argumentSecond;
    std::optional<Operation> m_operation;
    double m_value;
};