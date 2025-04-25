#pragma once

#include <optional>
#include <set>
#include <string>
#include <map>

namespace Operations {
    const std::string ADD = "+";
    const std::string SUBTRACT = "-";
    const std::string MULTIPLY = "*";
    const std::string DIVIDE = "/";
    const std::string EQUAL = "=";
    const std::string OPERATIONS_STRING = ADD + SUBTRACT + MULTIPLY + DIVIDE + EQUAL;
}

enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

std::optional<Operation> StringToOperation(const std::string& op);