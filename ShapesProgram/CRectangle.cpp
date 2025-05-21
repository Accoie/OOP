#include "CRectangle.h"

CRectangle::CRectangle(CPoint startPoint, double width, double height, uint32_t fillColor, uint32_t outlineColor)
    : m_startPoint(startPoint), m_width(width), m_height(height), m_fillColor(fillColor), m_outlineColor(outlineColor)
{
    if (m_width < 0) throw std::invalid_argument("Width can't be negative");
    if (m_height < 0) throw std::invalid_argument("Height can't be negative");
}

double CRectangle::GetArea() const 
{
    return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
    return (m_height + m_width) * 2;
}

std::string CRectangle::ToString() const
{
    std::string result = "Left Top: " + GetLeftTop().ToString() + "\n"
        + "Right Bottom: " + GetRightBottom().ToString() + "\n"
        + "Width: " + std::to_string(m_width) + "\n"
        + "Height: " + std::to_string(m_height) + "\n"
        + "Fill color: " + ColorToHex(m_fillColor) + "\n"
        + "Outline color: " + ColorToHex(m_outlineColor) + "\n";

    return result;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_startPoint;
}

CPoint CRectangle::GetRightBottom() const 
{
    return CPoint(m_startPoint.GetX() + m_width, m_startPoint.GetY() - m_height);
}

double CRectangle::GetWidth() const 
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

void CRectangle::Draw(ICanvas& canvas)
{
    canvas.FillRect(m_startPoint, m_width, m_height, m_fillColor, m_outlineColor);
}