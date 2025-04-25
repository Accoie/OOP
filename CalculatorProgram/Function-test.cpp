#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Function.h"
#include "../Variable.h"
#include <cmath>

TEST_CASE("Create default function with 1 argument")
{
    std::shared_ptr<Variable> var = Variable::CreateVariable("sdf", std::nullopt, 3.3);
    std::shared_ptr<Function> func = Function::CreateFunction("nam", var);
    CHECK(func->GetName() == "nam");
    CHECK(func->GetValue() == 3.3);
}

TEST_CASE("Function value calculation") {
    std::shared_ptr<Variable> var1 = Variable::CreateVariable("x", std::nullopt, 10.2);
    std::shared_ptr<Variable> var2 = Variable::CreateVariable("y", std::nullopt, 3.522);

    std::shared_ptr<Function> func = Function::CreateFunction(
        "test",
        var1,
        var2,
        Operation::Add
    );

    std::shared_ptr<Variable> var3 = Variable::CreateVariable("y", func, std::nullopt);

    std::shared_ptr<Function> func1 = Function::CreateFunction(
        "test1",
        var1,
        var2,
        Operation::Subtract
    );

    std::shared_ptr<Function> func2 = Function::CreateFunction(
        "test2",
        var1,
        var2,
        Operation::Multiply
    );

    std::shared_ptr<Function> func3 = Function::CreateFunction(
        "test3",
        var1,
        var2,
        Operation::Divide
    );

    CHECK(var3->GetValue() == 13.722);
    CHECK(std::fabs(func1->GetValue() - 6.678) < 1e-8);
    CHECK(func2->GetValue() == 35.9244);
    CHECK(std::fabs(func3->GetValue() - 2.8960817717) < 1e-8);
}

TEST_CASE("Function divide 0") {
    std::shared_ptr<Variable> var1 = Variable::CreateVariable("x", std::nullopt, 10.2);
    std::shared_ptr<Variable> var2 = Variable::CreateVariable("y", std::nullopt, 0.0);

    std::shared_ptr<Function> func = Function::CreateFunction(
        "test",
        var1,
        var2,
        Operation::Divide
    );

    CHECK(std::isnan(func->GetValue()));
}

TEST_CASE("Nan in argument")
{
    std::shared_ptr<Variable> var1 = Variable::CreateVariable("x", std::nullopt, 10.2);
    std::shared_ptr<Variable> var2 = Variable::CreateVariable("y", std::nullopt, NAN);
    std::shared_ptr<Variable> var3 = Variable::CreateVariable("z", std::nullopt, NAN);

    std::shared_ptr<Function> func = Function::CreateFunction(
        "test",
        var1,
        var2,
        Operation::Divide
    );

    std::shared_ptr<Function> func1 = Function::CreateFunction(
        "test1",
        var1,
        var2,
        Operation::Add
    );

    std::shared_ptr<Function> func2 = Function::CreateFunction(
        "test2",
        var2,
        var3,
        Operation::Multiply
    );

    CHECK(std::isnan(func->GetValue()));
    CHECK(std::isnan(func1->GetValue()));
    CHECK(std::isnan(func2->GetValue()));
}

TEST_CASE("Function value calculation(arguments: function, variable)") {
    std::shared_ptr<Variable> var1 = Variable::CreateVariable("x", std::nullopt, 10.2);
    std::shared_ptr<Variable> var2 = Variable::CreateVariable("y", std::nullopt, 3.522);

    std::shared_ptr<Function> func = Function::CreateFunction(
        "test",
        var1,
        var2,
        Operation::Add
    );

    std::shared_ptr<Function> func1 = Function::CreateFunction(
        "test1",
        func,
        var2,
        Operation::Subtract
    );

    CHECK(func1->GetValue() == 10.2);
}