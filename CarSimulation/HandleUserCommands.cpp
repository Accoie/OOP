#include "HandleUserCommands.h"

int HandleUserCommands(Car& car, std::string command, std::string valueString)
{
    int value = 0;
    if (COMMANDS.find(command) != COMMANDS.end())
    {
        if (command == ENGINE_ON)
        {
            car.TurnOnEngine();
        } 
        else if (command == ENGINE_OFF)
        {
            car.TurnOffEngine();
        } 
        else if (command == INFO)
        {
            car.Info();
        } 
        else
        {
            try
            {
                size_t pos = 0;
                value = std::stoi(valueString, &pos);

                if (pos != valueString.size()) {
                    throw std::invalid_argument("Invalid command argument: extra characters after number\n");
                }

                command == SET_GEAR ? car.SetGear(value) : car.SetSpeed(value);
            }
            catch(std::invalid_argument)
            {
                std::cout << "Invalid command argument\n";
                return 1;
            }
            catch (std::out_of_range)
            {
                std::cout << "Invalid command argument: number is too big\n";
                return 1;
            }
        }
    } 
    else
    {
        std::cout << "Unknown command\n";
        return 1;
    }
    return 0;
}