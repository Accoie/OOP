#pragma once
#include "IShape.h"
#include "CRectangle.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class CShapesHandler
{
public:
    void HandleInputShapes();
    void PrintShapesInfo();
    void DrawShapes(sf::RenderWindow& window);
    CShapesHandler(std::istream& input,
        std::ostream& output);
private:
    void HandleShape(std::string shape);

    void HandleRectangle(std::string rectangleStr);
    void HandleTriangle(std::string triangleStr);
    void HandleCircle(std::string circleStr);
    void HandleLineSegment(std::string lineSegmentStr);

    const IShape* GetMaxAreaShape() const;
    const IShape* GetMinPerimeterShape() const;

    std::istream &m_input;
    std::ostream &m_output;

    std::vector<std::unique_ptr<IShape>> m_shapes;
};

