#pragma once

#include "Argument.h"
#include <cmath>
#include <string>



class Variable
{
public:
    std::string GetName() const;
    double GetValue() const;
    static std::shared_ptr<Variable> CreateVariable(std::string name, std::optional<ArgumentType> arg = std::nullopt, std::optional<double> value = std::nullopt);
    void ChangeValue(double value);
    void ChangeArgument(ArgumentType arg);
private:
    Variable(std::string name, std::optional<ArgumentType> arg, double value)
        : m_name(name),
        m_arg(arg),
        m_value(value)
    {
    };
    std::string m_name;
    std::optional<ArgumentType> m_arg;
    double m_value = NAN;
};

