#include "Operation.h"


std::optional<Operation> StringToOperation(const std::string& op) {
    static const std::map<std::string, Operation> opMap = {
        {Operations::ADD, Operation::Add},
        {Operations::SUBTRACT, Operation::Subtract},
        {Operations::MULTIPLY, Operation::Multiply},
        {Operations::DIVIDE, Operation::Divide}
    };

    auto it = opMap.find(op);
    if (it != opMap.end()) {
        return it->second;
    }
    return std::nullopt;
}