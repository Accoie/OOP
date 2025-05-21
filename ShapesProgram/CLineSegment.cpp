#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color)
    : m_startPoint(startPoint), m_endPoint(endPoint), m_color(color) {};

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return m_startPoint.GetDistanceToPoint(m_endPoint);
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_color;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

std::string CLineSegment::ToString() const
{
    return "Start point: " + m_startPoint.ToString() + "\n"
        + "End point: " + m_endPoint.ToString() + "\n"
        + "Color: " + ColorToHex(m_color) + "\n";
}

void CLineSegment::Draw(ICanvas& canvas)
{
    canvas.DrawLine(m_startPoint, m_endPoint, m_color);
}