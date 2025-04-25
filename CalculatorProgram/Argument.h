#pragma once

#include <variant>
#include <memory>
#include <optional>
#include <string>

class Variable;
class Function;

using ArgumentType = std::variant<
    std::shared_ptr<Variable>,
    std::shared_ptr<Function>
>;

std::string GetArgumentName(const ArgumentType& argument);
double GetArgumentValue(const ArgumentType& argument);
