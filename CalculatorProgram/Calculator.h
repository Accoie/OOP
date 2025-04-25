#pragma once
#include <vector>
#include <optional>
#include <string>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include "Argument.h"

using FunctionsType = std::vector<std::shared_ptr<Function>>;
using VariablesType = std::vector<std::shared_ptr<Variable>>;

enum StatusOfValidateFunction {
    functionOneArgument,
    functionTwoArguments,
};
enum StatusOfValidateVariable {
    changeValue,
    defineVar,
};

class Calculator
{
public:

    bool AddToFunctions(std::string name, 
        std::string argFirstName,
        std::optional<std::string> argSecondName = std::nullopt,
        std::optional<std::string> op = std::nullopt);

    bool AddToVariables(std::string name, std::optional<std::string> arg = std::nullopt, std::optional<double> value = std::nullopt);
    const VariablesType& GetVariables() const;
    const FunctionsType& GetFunctions() const;
    FunctionsType::iterator FindInFunctions(std::string name);
    VariablesType::iterator  FindInVariables(std::string name);
    void PrintFunctions(std::ostream &out = std::cout);
    void PrintVariables(std::ostream &out = std::cout);
    void PrintValue(const std::vector<std::string>& tokens, std::ostream& out = std::cout);
private:
    
    
    

    bool CheckExistOperation(std::string op);
    bool CheckArgumentExist(std::string name);
    StatusOfValidateFunction ValidateFunction(std::string name,
        std::string argFirstName,
        std::optional<std::string> argSecondName = std::nullopt,
        std::optional<std::string> op = std::nullopt);

    
    StatusOfValidateVariable ValidateVariable(std::string name, std::optional<std::string> argName, std::optional<double> value);


    std::optional<ArgumentType> FindArgument(std::string name);

    std::shared_ptr<Function> MakeFunction(std::string name,
        std::string argFirstName,
        std::optional<std::string> argSecondName,
        std::optional<std::string> op);
    std::shared_ptr<Variable> MakeVariable(std::string name, std::optional<std::string> argName, std::optional<double> value);

    void ActualizeFunctions(std::shared_ptr<Variable>& updatedVariable);
    void UpdateFunctions(std::queue<std::shared_ptr<Function>> &updatingFunctions, std::shared_ptr<Function>& updatedFunction);
    FunctionsType m_functions;
    VariablesType m_variables;
};

