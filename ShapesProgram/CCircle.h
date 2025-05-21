#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle :
    public ISolidShape
{
public: 
    CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor);

    std::string ToString() const override;

    double GetArea() const override;
    double GetPerimeter() const override;
   
    uint32_t GetFillColor() const override;
    uint32_t GetOutlineColor() const override;

    CPoint GetCenter() const;
    double GetRadius() const;

    void Draw(ICanvas& canvas) override;
private:
    CPoint m_center;
    double m_radius;

    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};

