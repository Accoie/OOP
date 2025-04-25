#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HandleUserCommands.h"
#include "../Calculator.h"
#include "../Variable.h"
#include "../Function.h"
#include <sstream>
#include <iostream>
#include <limits>
#include <format>

const double MAX_DOUBLE = std::numeric_limits<double>::max();
const double MIN_DOUBLE = std::numeric_limits<double>::min();

TEST_CASE("HandleUserCommands processes empty input correctly")
{
    Calculator calc;
    HandleUserCommands(calc, "");
    CHECK(true);
}

TEST_CASE("HandleUserCommands processes var command") // VAR COMMAND
{
    Calculator calc;
    HandleUserCommands(calc, "var x");
    CHECK(calc.FindInVariables("x") != calc.GetVariables().end());
}

TEST_CASE("HandleUserCommands processes let command") // LET COMMAND
{
    Calculator calc;
    HandleUserCommands(calc, "let x = 5");
    auto var = calc.FindInVariables("x");
    CHECK(var != calc.GetVariables().end());
    CHECK((*var)->GetValue() == 5);
}

TEST_CASE("HandleUserCommands processes fn command") // FN COMMAND
{
    Calculator calc;
    HandleUserCommands(calc, "let x = 5");
    HandleUserCommands(calc, "let y = 6");
    SECTION("equal") {
        HandleUserCommands(calc, "fn f = x");
        auto it = calc.FindInFunctions("f");

        CHECK(it != calc.GetFunctions().end());
        CHECK((*it)->GetValue() == 5);
    }
    SECTION("add") {
        HandleUserCommands(calc, "fn f1 = x + y");
        auto it = calc.FindInFunctions("f1");

        CHECK(it != calc.GetFunctions().end());
        CHECK((*it)->GetValue() == 11);
    }
    SECTION("subtract") {
        HandleUserCommands(calc, "fn f2 = x - y");
        auto it = calc.FindInFunctions("f2");

        CHECK(it != calc.GetFunctions().end());
        CHECK((*it)->GetValue() == -1);
    }
    SECTION("divide") {
        HandleUserCommands(calc, "fn f3 = x / y");
        auto it = calc.FindInFunctions("f3");

        CHECK(it != calc.GetFunctions().end());
        CHECK((*it)->GetValue() == Approx(0.8333333333));
    }
    SECTION("multiply") {
        HandleUserCommands(calc, "fn f4 = x * y");
        auto it = calc.FindInFunctions("f4");

        CHECK(it != calc.GetFunctions().end());
        CHECK((*it)->GetValue() == 30);
    }
    SECTION("divide by zero") {
        HandleUserCommands(calc, "let z = 0");
        HandleUserCommands(calc, "fn f3 = x / z");
        auto it = calc.FindInFunctions("f3");

        CHECK(it != calc.GetFunctions().end());
        CHECK(std::isnan((*it)->GetValue()));
    }
}


TEST_CASE("HandleUserCommands processes print command") // PRINT COMMAND
{
    Calculator calc;
    HandleUserCommands(calc, "let x = 10");

    std::ostringstream ss;
    HandleUserCommands(calc, "print x", ss);

    CHECK(ss.str().find("10.00") != std::string::npos);
}

TEST_CASE("HandleUserCommands processes printvars command") // PRINTVARS
{
    Calculator calc;
    HandleUserCommands(calc, "var x");
    HandleUserCommands(calc, "let x = 15");
    std::ostringstream ss;
    HandleUserCommands(calc, "printvars", ss);
    

    CHECK(ss.str().find("x:15.00") != std::string::npos);
}

TEST_CASE("HandleUserCommands processes printfns command")
{
    Calculator calc;
    HandleUserCommands(calc, "var x");
    HandleUserCommands(calc, "let x = 20");
    std::ostringstream ss;
    HandleUserCommands(calc, "fn f = x", ss);
    HandleUserCommands(calc, "printfns", ss);

    CHECK(ss.str().find("f:20.00") != std::string::npos);
}

TEST_CASE("HandleUserCommands handles unknown command")
{
    Calculator calc;
    std::ostringstream ss;
    HandleUserCommands(calc, "unknown cmd", ss);
    CHECK(ss.str().find("unknown cmd") == std::string::npos);
}

TEST_CASE("HandleUserCommands passes correct tokens to commands")
{
    Calculator calc;
    
    SECTION("Var tests") {
        HandleUserCommands(calc, "var 1dsfsd"); // œ–Œ¬≈– ¿ ID — ÷»‘–€
        CHECK(calc.FindInVariables("1dsfsd") == calc.GetVariables().end()); 
        CHECK(calc.FindInVariables("1") == calc.GetVariables().end());
        HandleUserCommands(calc, "var ˚‚‡‚˚"); // œ–Œ¬≈– ¿ Õ¿  »–»ÀÀ»÷”
        CHECK(calc.FindInVariables("˚‚‡‚˚") == calc.GetVariables().end());
        HandleUserCommands(calc, "var dffËËË"); // œ–Œ¬≈– ¿ Õ¿  »–»ÀÀ»÷”
        CHECK(calc.FindInVariables("dffËËË") == calc.GetVariables().end());
        HandleUserCommands(calc, "var df_bo"); // œ–Œ¬≈– ¿ Õ¿ Õ»∆Õ≈≈ œŒƒ◊≈– »¬¿Õ»≈
        CHECK(calc.FindInVariables("df_bo") != calc.GetVariables().end());
    }

    SECTION("Let tests") { 
       
        SECTION("Cyrillic")
        {
            HandleUserCommands(calc, "let ‡‚‚‡=5"); // œ–Œ¬≈– ¿ Õ¿  »–»ÀÀ»÷”
            CHECK(calc.FindInVariables("‡‚‚‡") == calc.GetVariables().end());
        }
        SECTION("Space recognitions")
        {
            HandleUserCommands(calc, "let x=5");// –¿—œŒ«Õ¿¬¿Õ»≈ œ–Œ¡≈ÀŒ¬
            HandleUserCommands(calc, "let y=     5");// –¿—œŒ«Õ¿¬¿Õ»≈ œ–Œ¡≈ÀŒ¬
            HandleUserCommands(calc, "let z     =5");// –¿—œŒ«Õ¿¬¿Õ»≈ œ–Œ¡≈ÀŒ¬
            CHECK(calc.FindInVariables("x") != calc.GetVariables().end());
            CHECK(calc.FindInVariables("y") != calc.GetVariables().end());
            CHECK(calc.FindInVariables("z") != calc.GetVariables().end());
        }
        
        SECTION("Check value")
        {
            
          
            std::ostringstream ss;
            SECTION("MAX") 
            {
                ss << std::to_string(MAX_DOUBLE);
                std::cout << ss.str();
                HandleUserCommands(calc, "let b=" + ss.str()); // Ã¿ —»Ã”Ã Õ¿ ¬¬Œƒ≈
                CHECK(calc.FindInVariables("b") != calc.GetVariables().end());
                CHECK((*calc.FindInVariables("b"))->GetValue() == Approx(MAX_DOUBLE));
            }
            
            SECTION("MIN")
            {

                ss << std::scientific << std::setprecision(std::numeric_limits<double>::max_digits10 - 1) << MIN_DOUBLE;
                HandleUserCommands(calc, "let b=" + ss.str()); // Ã»Õ»Ã”Ã Õ¿ ¬¬Œƒ≈
                CHECK(calc.FindInVariables("b") != calc.GetVariables().end());
                CHECK((*calc.FindInVariables("b"))->GetValue() == Approx(MIN_DOUBLE));
            }
            
            SECTION("MORE THAN MAX")
            {
                
                ss << "1.79769e+309";
                HandleUserCommands(calc, "let x=" + ss.str()); // ¡ŒÀ‹ÿ≈ Ã¿ — Õ¿ ¬¬Œƒ≈
                
                CHECK(calc.FindInVariables("x") == calc.GetVariables().end());
            }
            
            SECTION("LESS THAN MIN")
            {
                ss << "2.2250738585072014e-309";
                HandleUserCommands(calc, "let c=" + ss.str()); // Ã≈Õ‹ÿ≈ Ã»Õ Õ¿ ¬¬Œƒ≈
                CHECK(calc.FindInVariables("c") == calc.GetVariables().end());
            }
            
        }
        
    }
    
    SECTION("fn")
    {
        std::ostringstream ss;
        
        SECTION("Cyrillic")
        {
            HandleUserCommands(calc, "let c=5"); 
            HandleUserCommands(calc, "let b=5"); 
            HandleUserCommands(calc, "fn ‡‚‚‡=c+b"); // œ–Œ¬≈– ¿ Õ¿  »–»ÀÀ»÷”
            CHECK(calc.FindInFunctions("‡‚‚‡") == calc.GetFunctions().end());
        }
        
        
        SECTION("Maximum") {
            ss << std::to_string(MAX_DOUBLE);
            HandleUserCommands(calc, "let b= 1.79769e+308"); // Ã¿ —»Ã”Ã Õ¿ ¬¬Œƒ≈
            HandleUserCommands(calc, "let Ò=" + ss.str()); // Ã¿ —»Ã”Ã Õ¿ ¬¬Œƒ≈
            HandleUserCommands(calc, "fn f = b + b");
            CHECK(calc.FindInFunctions("f") == calc.GetFunctions().end());//‡ÁÓ·‡Ú¸Òˇ ÔÓ˜ÂÏÛ ÌÂ ÒÓÁ‰‡ÂÚÒˇ ÙÛÍÌˆËˇ
            HandleUserCommands(calc, "fn d = b * b");
            CHECK(calc.FindInFunctions("d") == calc.GetFunctions().end());
        }
        SECTION("MINIMUM") {
            ss << std::scientific << std::setprecision(std::numeric_limits<double>::max_digits10 - 1) << MIN_DOUBLE;
            HandleUserCommands(calc, "let x=" + ss.str()); // Ã»Õ»Ã”Ã Õ¿ ¬¬Œƒ≈
            HandleUserCommands(calc, "let y=" + ss.str()); // Ã»Õ»Ã”Ã Õ¿ ¬¬Œƒ≈
            HandleUserCommands(calc, "fn f = x + y");
            CHECK(calc.FindInFunctions("f") != calc.GetFunctions().end());
        }
        SECTION("Space tests")
        {
            HandleUserCommands(calc, "let b=1");
            HandleUserCommands(calc, "let c=2");
            HandleUserCommands(calc, "fn f=b+c");
            CHECK((*calc.FindInFunctions("f"))->GetValue() == Approx(3));
            HandleUserCommands(calc, "fn f1=b+  c");
            CHECK((*calc.FindInFunctions("f1"))->GetValue() == Approx(3));
            HandleUserCommands(calc, "fn f2=b     +c");
            CHECK((*calc.FindInFunctions("f2"))->GetValue() == Approx(3));
            HandleUserCommands(calc, "fn f3=     b+c");
            CHECK((*calc.FindInFunctions("f"))->GetValue() == Approx(3));
        }
        SECTION("Square circle")
        {
            HandleUserCommands(calc, "var radius");
            HandleUserCommands(calc, "let pi = 3.14159265");
            HandleUserCommands(calc, "fn radiusSquared = radius * radius");
            HandleUserCommands(calc, "fn circleArea = pi * radiusSquared");
            HandleUserCommands(calc, "let radius = 10");
            CHECK((*calc.FindInFunctions("circleArea"))->GetValue() == Approx(314.16));
            HandleUserCommands(calc, "let circle10Area = circleArea");
            HandleUserCommands(calc, "let radius = 20");
            HandleUserCommands(calc, "let circle20Area = circleArea");
            CHECK((*calc.FindInFunctions("circleArea"))->GetValue() == Approx(1256.64));
            CHECK((*calc.FindInFunctions("radiusSquared"))->GetValue() == Approx(400.00));
        }
        SECTION("Fibbonachi")
        {
            HandleUserCommands(calc, "let v0=0");
            HandleUserCommands(calc, "let v1=1");
            HandleUserCommands(calc, "fn fib0=v0");
            HandleUserCommands(calc, "fn fib1 = v1");
            HandleUserCommands(calc, "fn fib2 = fib1 + fib0");
            HandleUserCommands(calc, "fn fib3 = fib2 + fib1");
            HandleUserCommands(calc, "fn fib4 = fib3 + fib2");
            HandleUserCommands(calc, "fn fib5 = fib4 + fib3");
            HandleUserCommands(calc, "fn fib6 = fib5 + fib4");
            CHECK((*calc.FindInFunctions("fib6"))->GetValue() == 8);
            HandleUserCommands(calc, "let v0=1");
            HandleUserCommands(calc, "let v1=1");
            CHECK((*calc.FindInFunctions("fib6"))->GetValue() == 13);
        }
    }
    
}