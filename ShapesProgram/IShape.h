#pragma once

#include "ICanvasDrawable.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <map>

namespace SHAPES {
const std::string RECTANGLE = "rectangle";
const std::string CIRCLE = "circle";
const std::string TRIANGLE = "triangle";
const std::string LINE_SEGMENT = "lineSegment";
}
enum Shapes {
    rectangle,
    circle,
    triangle,
    lineSegment
};

const std::map<std::string, Shapes> shapesMap = {
    {SHAPES::RECTANGLE, Shapes::rectangle},
    {SHAPES::CIRCLE, Shapes::circle},
    {SHAPES::TRIANGLE, Shapes::triangle},
    {SHAPES::LINE_SEGMENT, Shapes::lineSegment}
};

class IShape : public ICanvasDrawable
{
public:
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual std::string ToString() const = 0;
    virtual uint32_t GetOutlineColor() const = 0;
    std::string ColorToHex(uint32_t color) const;

    virtual ~IShape() = default;
private:
};

