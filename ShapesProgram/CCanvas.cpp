#include "CCanvas.h"

const float LINE_THICKNESS = 2.0f;

CCanvas::CCanvas(sf::RenderWindow& window) : m_window(window)
{
}

sf::Vector2f CCanvas::ToVector2f(double x, double y) const
{
    return(sf::Vector2f((float) x, (float) y));
}

void CCanvas::DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) const
{
    sf::Vertex line[] =
    {
        sf::Vertex(ToVector2f(startPoint.GetX(), startPoint.GetY()), sf::Color(lineColor)),
        sf::Vertex(ToVector2f(endPoint.GetX(), endPoint.GetY()), sf::Color(lineColor))
    };

    m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor, uint32_t outlineColor) const
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());

    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, ToVector2f(points[i].GetX(), points[i].GetY()));
    }

    polygon.setFillColor(sf::Color(fillColor));
    polygon.setOutlineColor(sf::Color(outlineColor));
    polygon.setOutlineThickness(LINE_THICKNESS);

    m_window.draw(polygon);
}

void CCanvas::FillRect(CPoint coordinates, double width, double height, uint32_t fillColor, uint32_t outlineColor) const
{
    sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    rect.setPosition(ToVector2f(coordinates.GetX(), coordinates.GetY()));
    rect.setFillColor(sf::Color(fillColor));
    rect.setOutlineColor(sf::Color(outlineColor));
    rect.setOutlineThickness(LINE_THICKNESS);

    m_window.draw(rect);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) const
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(ToVector2f(center.GetX(), center.GetY()) - ToVector2f(radius, radius));
    circle.setFillColor(sf::Color(fillColor));
    circle.setOutlineColor(sf::Color(outlineColor));
    circle.setOutlineThickness(LINE_THICKNESS);

    m_window.draw(circle);
}