#include "DriveCar.h"

void DriveCar(Car& car)
{
    while (true)
    {
        std::string line = "";
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string command;
        std::string valueString = "";

        ss >> command >> valueString;

        if (line == "...")
        {
            break;
        }
        HandleUserCommands(car, command, valueString);
    }
}