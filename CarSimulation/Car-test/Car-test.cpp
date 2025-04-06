#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car.h"
#include <sstream>

//�������� ����� ��� ���� ���������
TEST_CASE("Speed limits for each gear")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Reverse gear (-1)")
    {
        REQUIRE(car.SetGear(-1));
        REQUIRE(car.SetSpeed(0));    // �����������
        REQUIRE(car.SetSpeed(20));   // ������������
        REQUIRE_FALSE(car.SetSpeed(21));  // ������ ������������
        REQUIRE_FALSE(car.SetSpeed(-1));  // ������ �����������
    }

    SECTION("Neutral gear (0)")
    {
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(0));
        REQUIRE(car.SetSpeed(30));   // ������� ��������
        REQUIRE_FALSE(car.SetSpeed(31)); // ������ ���������
        REQUIRE(car.SetSpeed(20));   // ����� ���������
        REQUIRE(car.SetSpeed(0));    // �����������
        REQUIRE_FALSE(car.SetSpeed(-1)); // ������ �����������
    }

    SECTION("First gear (1)")
    {
        REQUIRE(car.SetGear(1));
        REQUIRE(car.SetSpeed(0));    // �����������
        REQUIRE(car.SetSpeed(30));   // ������������
        REQUIRE_FALSE(car.SetSpeed(31));  // ������ ������������
        REQUIRE_FALSE(car.SetSpeed(-1));  // ������ �����������
    }

    SECTION("Second gear (2)")
    {
        car.SetGear(1);
        car.SetSpeed(20);
        REQUIRE(car.SetGear(2));
        REQUIRE(car.SetSpeed(20));   // �����������
        REQUIRE(car.SetSpeed(50));   // ������������
        REQUIRE_FALSE(car.SetSpeed(51));  // ������ ������������
        REQUIRE_FALSE(car.SetSpeed(19));  // ������ �����������
    }

    SECTION("Third gear (3)")
    {
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE(car.SetGear(3));
        REQUIRE(car.SetSpeed(30));   // �����������
        REQUIRE(car.SetSpeed(60));   // ������������
        REQUIRE_FALSE(car.SetSpeed(61));  // ������ ������������
        REQUIRE_FALSE(car.SetSpeed(29));  // ������ �����������
    }

    SECTION("Fourth gear (4)")
    {
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
        car.SetSpeed(40);
        REQUIRE(car.SetGear(4));
        REQUIRE(car.SetSpeed(40));   // �����������
        REQUIRE(car.SetSpeed(90));   // ������������
        REQUIRE_FALSE(car.SetSpeed(91));  // ������ ������������
        REQUIRE_FALSE(car.SetSpeed(39));  // ������ �����������
    }

    SECTION("Fifth gear (5)")
    {
        car.SetGear(1);
        car.SetSpeed(20);
        car.SetGear(2);
        car.SetSpeed(50);
        REQUIRE(car.SetGear(5));
        REQUIRE(car.SetSpeed(50));   // �����������
        REQUIRE(car.SetSpeed(150));  // ������������
        REQUIRE_FALSE(car.SetSpeed(151)); // ������ ������������
        REQUIRE_FALSE(car.SetSpeed(49));  // ������ �����������
    }
}

TEST_CASE("Gear shifting at boundary speeds for each gear")
{
    Car car;
    car.TurnOnEngine();

    SECTION("Reverse gear (-1)") {
        // ��������� ������ ��������
        REQUIRE(car.SetGear(-1));

        // �������� ��� ������ ���������
        SECTION("At zero speed") {
            REQUIRE(car.SetSpeed(0));
            REQUIRE(car.SetGear(1));  // ����� ������������� �� 1
        }
        SECTION("At min speed (0)") {
            REQUIRE(car.SetSpeed(0));
            REQUIRE(car.SetGear(0));  // ����� �� ��������
        }
        SECTION("At max speed (20)") {
            REQUIRE(car.SetSpeed(20));
            REQUIRE_FALSE(car.SetGear(1)); // ������ � ������ �� 1 ��� ��������
        }
        SECTION("Above max speed (21)") {
            car.SetSpeed(20);
            REQUIRE_FALSE(car.SetSpeed(21)); // ������ ��������� ��������
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
            REQUIRE_FALSE(car.SetSpeed(31)); // ������ ��������� ��������
        }
    }

    SECTION("Second gear (2)") {
        car.SetGear(1);
        car.SetSpeed(20);
        REQUIRE(car.SetGear(2));

        SECTION("At min speed (20)") {
            REQUIRE(car.SetSpeed(20));
            REQUIRE(car.SetGear(1));  // ����� ������������� �� 1
            REQUIRE_FALSE(car.SetGear(3));  // ������ ������������� �� 3
        }
        SECTION("At max speed (50)") {
            REQUIRE(car.SetSpeed(50));
            REQUIRE_FALSE(car.SetGear(1)); // ������ ������������� �� 1
            REQUIRE(car.SetGear(3)); // ����� ������������� �� 3
        }
        SECTION("Below min speed (19)") {
            REQUIRE_FALSE(car.SetSpeed(19)); // ������ ���������� ���� ��������
        }
    }

    // ����������� ����� ��� ������� 3-5
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
        REQUIRE(car.SetGear(0));  // ������������ �� ��������

        SECTION("Try shift from neutral at speed") {
            REQUIRE(car.SetGear(2)); // ����� ������������� � ��������
        }
    }

    SECTION("Attempt invalid shifts") {
        REQUIRE_FALSE(car.SetGear(-2));  // �������������� ��������
        REQUIRE_FALSE(car.SetGear(6));   // �������������� ��������
    }
}