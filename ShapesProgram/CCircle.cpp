#include "CCircle.h"
#include <cmath>
#include <numbers>

const double PI = std::numbers::pi;

CCircle::CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor)
    : m_center(center), m_radius(radius), m_outlineColor(outlineColor), m_fillColor(fillColor) {
    if (radius < 0) throw std::invalid_argument("Radius can't be negative");
};

std::string CCircle::ToString() const 
{
    return "Circle center: " + m_center.ToString() + "\n"
        + "Radius: " + std::to_string(m_radius) + "\n"
        + "Fill color: " + ColorToHex(m_fillColor) + "\n"
        + "Outline color: " + ColorToHex(m_outlineColor) + "\n";

};

double CCircle::GetArea() const
{
    return PI * m_radius * m_radius;
};

double CCircle::GetPerimeter() const
{
    return 2 * PI * m_radius;
};

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
};
uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
};

CPoint CCircle::GetCenter() const
{
    return m_center;
};

double CCircle::GetRadius() const
{
    return m_radius;
};

void CCircle::Draw(ICanvas& canvas)
{
    canvas.FillCircle(m_center, m_radius, m_fillColor, m_outlineColor);
}