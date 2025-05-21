#include "CPoint.h"

#include <cmath>

CPoint::CPoint(double x, double y) : m_x(x), m_y(y) {}

bool CPoint::operator==(const CPoint& point) const
{
    return m_x == point.GetX() && m_y == point.GetY();
}

double CPoint::GetX() const 
{
    return m_x;
}

double CPoint::GetY() const 
{
    return m_y;
}

std::string CPoint::ToString() const
{
   
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}
double CPoint::GetDistanceToPoint(const CPoint& point) const
{
    return std::hypot(point.m_x - m_x, point.m_y - m_y);
}