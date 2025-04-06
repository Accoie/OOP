#include "Car.h"
#include <map>


bool IsSpeedInRange(int speed, int min, int max) 
{
    return speed >= min && speed <= max;
}


const std::map<int, std::pair<int, int>> GEAR_SPEED_RANGES = {
    {-1, {0, 20}},
    {0, {0, INT_MAX}},  
    {1, {0, 30}},
    {2, {20, 50}},
    {3, {30, 60}},
    {4, {40, 90}},
    {5, {50, 150}}
};

bool Car::SetSpeed(int speed)
{
    if (speed < 0) 
    {
        std::cout << "Speed cannot be negative\n";
        return false;
    }

    if (!m_engine) 
    {
        std::cout << "Cannot set speed while engine is off\n";
        return false;
    }

    auto rangeIt = GEAR_SPEED_RANGES.find(m_gear);
    if (rangeIt == GEAR_SPEED_RANGES.end())
    {
        std::cout << "Invalid current gear\n";
        return false;
    }
    int minSpeed = (rangeIt->second).first;
    int maxSpeed = (rangeIt->second).second;

    if (m_gear == 0 && speed > m_speed) 
    {
        std::cout << "Cannot accelerate on neutral\n";
        return false;
    }

    if (!IsSpeedInRange(speed, minSpeed, maxSpeed)) 
    {
        std::cout << "Speed is out of gear range\n";
        return false;
    }


    if (speed == 0) {
        m_direction = standing_still;
    } 
    else if (m_gear == -1) 
    {
        m_direction = backward;
    } 
    else if (m_gear > 0) 
    {
        m_direction = forward;
    }

    m_speed = speed;
    return true;
}

bool Car::SetGear(int gear) 
{
    if (gear < -1 || gear > 5) 
    {
        std::cout << "Invalid gear\n";
        return false;
    }

    if (!m_engine) 
    {
        std::cout << "Cannot set gear while engine is off\n";
        return false;
    }

    if (gear == -1) 
    {
        if (m_speed != 0) 
        {
            std::cout << "Cannot reverse while moving\n";
            return false;
        }
        m_gear = gear;
        return true;
    }

    if (m_gear == -1 && m_speed != 0)
    {
        std::cout << "Car must be stopped to switch from reverse\n";
        return false;
    }

    auto rangeIt = GEAR_SPEED_RANGES.find(gear);
    if (rangeIt == GEAR_SPEED_RANGES.end()) 
    {
        std::cout << "Invalid target gear\n";
        return false;
    }

    const auto& [minSpeed, maxSpeed] = rangeIt->second;

    if (!IsSpeedInRange(m_speed, minSpeed, maxSpeed)) 
    {
        std::cout << "Unsuitable current speed for this gear\n";
        return false;
    }

    m_gear = gear;
    return true;
}


void Car::Info() const
{
    std::cout << "Engine: " << (IsTurnedOn() ? "on" : "off") << "\n"
        << "Direction: " << PrintDirection() << "\n"
        << "Speed: " << GetSpeed() << "\n"
        << "Gear: " << GetGear() << "\n";
}
bool Car::TurnOnEngine()
{
    m_engine = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (m_gear == 0 && m_direction == standing_still)
    {
        m_engine = false;
        return true;
    } 
    else
    {
        std::cout << "Car must be stopped and in neutral gear\n";
        return false;
    }
}

Direction Car::GetDirection() const
{
    return m_direction;
}

std::string Car::PrintDirection() const
{
    switch (m_direction)
    {
    case forward:
        return "forward";
    case backward:
        return "backward";
    case standing_still:
        return "standing still";
    }
    return "";
}