#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator.h"
#include "../Variable.h"
#include "../Function.h"
#include <cmath>
/*
TEST_CASE("Add new variable")
{
    Calculator calc;
    SECTION("without value and arg")
    {
        REQUIRE(calc.AddToVariables("asdfa"));
        VariablesType temp = calc.GetVariables();
        std::shared_ptr<Variable> var = *temp.begin();

        CHECK(var->GetName() == "asdfa");
        CHECK(std::isnan(var->GetValue()));
    }

    SECTION("with value")
    {
        REQUIRE(calc.AddToVariables("dddaaa", std::nullopt, 3.3333));
        VariablesType temp1 = calc.GetVariables();

        auto it = calc.FindInVariables("dddaaa");

        std::shared_ptr<Variable> var1 = *it;
        CHECK(var1->GetName() == "dddaaa");
        CHECK(var1->GetValue() == Approx(3.3333));
    }

    SECTION("with arg")
    {
        REQUIRE(calc.AddToVariables("base_var", std::nullopt, 2.5));
        REQUIRE(calc.AddToVariables("dependent_var", "base_var"));

        auto it = calc.FindInVariables("dependent_var");


        std::shared_ptr<Variable> var = *it;
        CHECK(var->GetName() == "dependent_var");
        CHECK(var->GetValue() == Approx(2.5));
    }

    SECTION("with empty name")
    {
        CHECK_FALSE(calc.AddToVariables(""));
    }

    SECTION("duplicate name")
    {
        REQUIRE(calc.AddToVariables("unique"));
        CHECK_FALSE(calc.AddToVariables("unique"));
    }
}
*/

TEST_CASE("Add new function")
{
    Calculator calc;

    // Подготовка переменных для тестов
    REQUIRE(calc.AddToVariables("x", std::nullopt, 5.0));
    REQUIRE(calc.AddToVariables("y", std::nullopt, 3.0));

    SECTION("one argument function")
    {
        REQUIRE(calc.AddToFunctions("f1", "x"));

        auto it = calc.FindInFunctions("f1");


        std::shared_ptr<Function> func = *it;
        CHECK(func->GetName() == "f1");
        CHECK(func->GetValue() == Approx(5.0));
    }

    SECTION("two arguments function")
    {
        REQUIRE(calc.AddToFunctions("sum", "x", "y", "+"));

        auto it = calc.FindInFunctions("sum");

        std::shared_ptr<Function> func = *it;
        CHECK(func->GetName() == "sum");
        CHECK(func->GetValue() == Approx(8.0)); 
    }
    
    SECTION("function with non-existent argument")
    {
        CHECK_FALSE(calc.AddToFunctions("bad_func", "non_existent_var"));
    }

    SECTION("duplicate function name")
    {
        REQUIRE(calc.AddToFunctions("func", "x"));
        CHECK_FALSE(calc.AddToFunctions("func", "y"));
    }

    SECTION("invalid operation")
    {
        CHECK_FALSE(calc.AddToFunctions("bad_op", "x", "y", "invalid_op"));
    }

    SECTION("missing operation for two args")
    {
        CHECK_FALSE(calc.AddToFunctions("missing_op", "x", "y"));
    }
}

TEST_CASE("Edge cases")
{
    Calculator calc;

    SECTION("add variable with non-existent argument")
    {
        CHECK_FALSE(calc.AddToVariables("bad_var", "non_existent"));
    }

    SECTION("add function with empty name")
    {
        CHECK_FALSE(calc.AddToFunctions("", "x"));
    }
}