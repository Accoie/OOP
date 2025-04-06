#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car.h"
#include <sstream>

//дописать тесты дл€ всех скоростей
TEST_CASE("Speed limits for each gear")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Reverse gear (-1)")
    {
        REQUIRE(car.SetGear(-1));
        REQUIRE(car.SetSpeed(0));    // минимальна€
        REQUIRE(car.SetSpeed(20));   // максимальна€
        REQUIRE_FALSE(car.SetSpeed(21));  // больше максимальной
        REQUIRE_FALSE(car.SetSpeed(-1));  // меньше минимальной
    }

    SECTION("Neutral gear (0)")
    {
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(0));
        REQUIRE(car.SetSpeed(30));   // текуща€ скорость
        REQUIRE_FALSE(car.SetSpeed(31)); // нельз€ увеличить
        REQUIRE(car.SetSpeed(20));   // можно уменьшить
        REQUIRE(car.SetSpeed(0));    // минимальна€
        REQUIRE_FALSE(car.SetSpeed(-1)); // меньше минимальной
    }

    SECTION("First gear (1)")
    {
        REQUIRE(car.SetGear(1));
        REQUIRE(car.SetSpeed(0));    // минимальна€
        REQUIRE(car.SetSpeed(30));   // максимальна€
        REQUIRE_FALSE(car.SetSpeed(31));  // больше максимальной
        REQUIRE_FALSE(car.SetSpeed(-1));  // меньше минимальной
    }

    SECTION("Second gear (2)")
    {
        car.SetGear(1);
        car.SetSpeed(20);
        REQUIRE(car.SetGear(2));
        REQUIRE(car.SetSpeed(20));   // минимальна€
        REQUIRE(car.SetSpeed(50));   // максимальна€
        REQUIRE_FALSE(car.SetSpeed(51));  // больше максимальной
        REQUIRE_FALSE(car.SetSpeed(19));  // меньше минимальной
    }

    SECTION("Third gear (3)")
    {
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(3));
        REQUIRE(car.SetSpeed(30));   // минимальна€
        REQUIRE(car.SetSpeed(60));   // максимальна€
        REQUIRE_FALSE(car.SetSpeed(61));  // больше максимальной
        REQUIRE_FALSE(car.SetSpeed(29));  // меньше минимальной
    }

    SECTION("Fourth gear (4)")
    {
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
        car.SetSpeed(40);
        REQUIRE(car.SetGear(4));
        REQUIRE(car.SetSpeed(40));   // минимальна€
        REQUIRE(car.SetSpeed(90));   // максимальна€
        REQUIRE_FALSE(car.SetSpeed(91));  // больше максимальной
        REQUIRE_FALSE(car.SetSpeed(39));  // меньше минимальной
    }

    SECTION("Fifth gear (5)")
    {
        car.SetGear(1);
        car.SetSpeed(20);
        car.SetGear(2);
        car.SetSpeed(50);
        REQUIRE(car.SetGear(5));
        REQUIRE(car.SetSpeed(50));   // минимальна€
        REQUIRE(car.SetSpeed(150));  // максимальна€
        REQUIRE_FALSE(car.SetSpeed(151)); // больше максимальной
        REQUIRE_FALSE(car.SetSpeed(49));  // меньше минимальной
    }
}

TEST_CASE("Gear shifting at boundary speeds for each gear")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Reverse gear (-1)") {
        // ”становка задней передачи
        REQUIRE(car.SetGear(-1));

        // ѕроверки при разных скорост€х
        SECTION("At zero speed") {
            REQUIRE(car.SetSpeed(0));
            REQUIRE(car.SetGear(1));  // ћожно переключитьс€ на 1
        }
        SECTION("At min speed (0)") {
            REQUIRE(car.SetSpeed(0));
            REQUIRE(car.SetGear(0));  // ћожно на нейтраль
        }
        SECTION("At max speed (20)") {
            REQUIRE(car.SetSpeed(20));
            REQUIRE_FALSE(car.SetGear(1)); // Ќельз€ с задней на 1 при движении
        }
        SECTION("Above max speed (21)") {
            car.SetSpeed(20);
            REQUIRE_FALSE(car.SetSpeed(21)); // Ќельз€ превысить максимум
        }
    }

    SECTION("First gear (1)") {
        REQUIRE(car.SetGear(1));

        SECTION("At min speed (0)") {
            REQUIRE(car.SetSpeed(0));
            REQUIRE_FALSE(car.SetGear(2));  
            REQUIRE_FALSE(car.GetGear() == 2); 
        }
        SECTION("At max speed (30)") {
            REQUIRE(car.SetSpeed(30));
            REQUIRE(car.SetGear(2)); 
        }
        SECTION("Above max speed (31)") {
            REQUIRE_FALSE(car.SetSpeed(31)); // Ќельз€ превысить максимум
        }
    }

    SECTION("Second gear (2)") {
        car.SetGear(1);
        car.SetSpeed(20);
        REQUIRE(car.SetGear(2));

        SECTION("At min speed (20)") {
            REQUIRE(car.SetSpeed(20));
            REQUIRE(car.SetGear(1));  // ћожно переключитьс€ на 1
            REQUIRE_FALSE(car.SetGear(3));  // Ќельз€ переключитьс€ на 3
        }
        SECTION("At max speed (50)") {
            REQUIRE(car.SetSpeed(50));
            REQUIRE_FALSE(car.SetGear(1)); // Ќельз€ переключитьс€ на 1
            REQUIRE(car.SetGear(3)); // ћожно переключитьс€ на 3
        }
        SECTION("Below min speed (19)") {
            REQUIRE_FALSE(car.SetSpeed(19)); // Ќельз€ опуститьс€ ниже минимума
        }
    }

    // јналогичные тесты дл€ передач 3-5
    SECTION("Third gear (3)") {
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(3));

        SECTION("At min speed (30)") {
            REQUIRE(car.SetSpeed(30));
            REQUIRE(car.SetGear(2));
            REQUIRE_FALSE(car.SetGear(4));
        }
        SECTION("At max speed (60)") {
            REQUIRE(car.SetSpeed(60));
            REQUIRE_FALSE(car.SetGear(2));
            REQUIRE(car.SetGear(4));
        }
    }

    SECTION("Fourth gear (4)") {
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
        car.SetSpeed(40);
        REQUIRE(car.SetGear(4));

        SECTION("At min speed (40)") {
            REQUIRE(car.SetSpeed(40));
            REQUIRE(car.SetGear(3));
            REQUIRE_FALSE(car.SetGear(5));
        }
    }

    SECTION("Fifth gear (5)") {
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
        car.SetSpeed(50);
        REQUIRE(car.SetGear(5));

        SECTION("At max speed (150)") {
            REQUIRE(car.SetSpeed(150));
            REQUIRE_FALSE(car.SetGear(4));
        }
    }
}

TEST_CASE("Special cases")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Neutral gear behavior") {
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(0));  // ѕереключение на нейтраль

        SECTION("Try shift from neutral at speed") {
            REQUIRE(car.SetGear(2)); // ћожно переключитьс€ с нейтрали
        }
    }

    SECTION("Attempt invalid shifts") {
        REQUIRE_FALSE(car.SetGear(-2));  // Ќесуществующа€ передача
        REQUIRE_FALSE(car.SetGear(6));   // Ќесуществующа€ передача
    }
}