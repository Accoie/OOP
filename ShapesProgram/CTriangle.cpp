#include "CTriangle.h"
#include <stdexcept>

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, uint32_t fillColor, uint32_t outlineColor) :
    m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3), m_fillColor(fillColor), m_outlineColor(outlineColor)
{
    if (CalculateDeterminant(m_vertex1, m_vertex2, m_vertex3) == 0)
    {
        throw std::invalid_argument("Determinant cannot be equal zero");
    }
}

double CTriangle::CalculateDeterminant(const CPoint& point1, const CPoint& point2, const CPoint& point3) const
{
    double determinant = (point1.GetX() - point3.GetX()) * (point2.GetY() - point3.GetY())
        - (point2.GetX() - point3.GetX()) * (point1.GetY() - point3.GetY());

    return determinant;
};

double CTriangle::GetArea() const 
{
    return 0.5 * abs(CalculateDeterminant(m_vertex1, m_vertex2, m_vertex3));
};

double CTriangle::GetPerimeter() const 
{
    double edge1 = m_vertex1.GetDistanceToPoint(m_vertex2);
    double edge2 = m_vertex2.GetDistanceToPoint(m_vertex3);
    double edge3 = m_vertex3.GetDistanceToPoint(m_vertex1);

    return edge1 + edge2 + edge3;
};

std::string CTriangle::ToString() const
{
    return "Vertex1: " + m_vertex1.ToString() + "\n"
        + "Vertex2: " + m_vertex2.ToString() + "\n"
        + "Vertex3: " + m_vertex3.ToString() + "\n";
        + "Outline color: " + ColorToHex(m_fillColor) + "\n"
        + "Fill color: " + ColorToHex(m_outlineColor) + "\n";
};

uint32_t CTriangle::GetOutlineColor() const 
{
    return m_outlineColor;
};

uint32_t CTriangle::GetFillColor() const 
{ 
    return m_fillColor; 
};

CPoint CTriangle::GetVertex1() const 
{
    return m_vertex1;
};

CPoint CTriangle::GetVertex2() const 
{
    return m_vertex2;
};

CPoint CTriangle::GetVertex3() const 
{
    return m_vertex3;
};

void CTriangle::Draw(ICanvas& canvas)
{
    canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 }, m_fillColor, m_outlineColor);
}