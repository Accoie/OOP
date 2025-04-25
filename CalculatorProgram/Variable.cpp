#include "Function.h"
#include "Variable.h"
#include "iostream"
#include <variant>

std::string Variable::GetName() const 
{ 
    return m_name; 
};
double Variable::GetValue() const 
{ 
    return m_value; 
};
void Variable::ChangeValue(double value)
{
    m_value = value;
};
void Variable::ChangeArgument(ArgumentType arg)
{
    m_arg = arg;
    m_value = GetArgumentValue(arg);
};

std::shared_ptr<Variable> Variable::CreateVariable(std::string name, std::optional<ArgumentType> arg, std::optional<double> value)
{
    value = arg.has_value() ? GetArgumentValue(arg.value()) : value;
    if (value == INFINITY)
    {
        throw std::out_of_range("Cannot be infinity");
    }
    return std::make_shared<Variable>(Variable(name, arg, value.value_or(NAN)));
}; 

