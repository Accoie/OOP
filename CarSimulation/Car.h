#pragma once
#include <iostream>
#include <string>

enum Direction {
    forward,
    backward,
    standing_still
};

class Car {
public:
    void Info() const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetSpeed(int speed);
    bool SetGear(int gear);
    bool IsTurnedOn() const { return m_engine; }
    int GetSpeed() const { return m_speed; }
    int GetGear() const { return m_gear; }
    std::string PrintDirection() const;
    Direction GetDirection() const;

private:
    const int MIN_SPEED = 0;
    const int MAX_SPEED = 150;
    const int MIN_GEAR = -1;
    const int MAX_GEAR = 5;

    bool m_engine = false;
    int m_gear = 0;
    int m_speed = 0;
    Direction m_direction = standing_still;

};