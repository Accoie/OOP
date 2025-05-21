#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle :
    public ISolidShape
{
public:
    double CalculateDeterminant(const CPoint &vertex1, const CPoint& vertex2, const CPoint& vertex3) const;
    CTriangle(const CPoint &vertex1, const CPoint &vertex2, const CPoint &vertex3, uint32_t fillColor, uint32_t outlineColor);
   
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetFillColor() const override;
    uint32_t GetOutlineColor() const override;
    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

    void Draw(ICanvas& canvas) override;
private:
    CPoint m_vertex1;
    CPoint m_vertex2;
    CPoint m_vertex3;

    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};

