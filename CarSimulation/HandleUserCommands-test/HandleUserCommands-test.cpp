#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HandleUserCommands.h"

TEST_CASE("Invalid command argument - string")
{
    Car car;
    CHECK(HandleUserCommands(car, SET_GEAR, "asdfasdf") == 1);
}
TEST_CASE("Invalid command argument - float")
{
    Car car;
    CHECK(HandleUserCommands(car, SET_GEAR, "4.5") == 1);
}
TEST_CASE("Invalid command argument - overflow number")
{
    Car car;
    CHECK(HandleUserCommands(car, SET_GEAR, "5000000000") == 1);
}
TEST_CASE("Unknown command")
{
    Car car;
    CHECK(HandleUserCommands(car, "DSFAS", "1") == 1);
}