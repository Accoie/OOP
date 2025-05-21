#pragma once
#include <string>
class CPoint
{
public:
    double GetX() const;
    double GetY() const;
    std::string ToString() const;
    double GetDistanceToPoint(const CPoint& point) const;
    CPoint(double x, double y);

    bool operator==(const CPoint& point) const;
private:
    double m_x;
    double m_y;
};

