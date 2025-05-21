#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
class CRectangle : public ISolidShape
{
public:
    CRectangle(CPoint startPos, double width, double height, uint32_t fillColor, uint32_t outlineColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetFillColor() const override;
    uint32_t GetOutlineColor() const override;
    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetWidth() const;
    double GetHeight() const;

    void Draw(ICanvas& canvas) override;
private:

    CPoint m_startPoint;
    double m_width;
    double m_height;

    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};

