#include "CShapesHandler.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CCanvas.h"

#include <sstream>
#include <string>

CShapesHandler::CShapesHandler(std::istream& input,
    std::ostream& output) : m_input(input), m_output(output) {};

void CShapesHandler::PrintShapesInfo()
{
    if (m_shapes.empty())
    {
        m_output << "No shapes" << std::endl;
        return;
    }

    m_output << "Shape with max area: \n";
    auto maxAreaShape = GetMaxAreaShape();
    m_output << maxAreaShape->ToString();

    m_output << "Shape with min perimeter: \n";
    auto minPerimetrShape = GetMinPerimeterShape();
    m_output << minPerimetrShape->ToString();

}

const IShape* CShapesHandler::GetMaxAreaShape() const 
{
    auto result = std::max_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) {
        return a->GetArea() < b->GetArea();
    });
    if (result != m_shapes.end())
    {
        return result->get();
    }

    return nullptr;
};

const IShape* CShapesHandler::GetMinPerimeterShape() const 
{
    auto result = std::min_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) {
        return a->GetPerimeter() < b->GetPerimeter();
        });

    if (result != m_shapes.end())
    {
        return result->get();
    }

    return nullptr;
};

uint32_t HexStringToUInt32(const std::string& hexStr) {
    return std::stoul(hexStr, nullptr, 16); 
}

void CShapesHandler::HandleRectangle(std::string rectangleStr)
{
    std::istringstream ss(rectangleStr);
    std::string rectangleName;
    double startPointX, startPointY, width, height;
    std::string outlineColorStr, fillColorStr;

    if (ss >> rectangleName >> startPointX >> startPointY >> width >> height >> fillColorStr >> outlineColorStr)
    {
        uint32_t outlineColor;
        uint32_t fillColor;
        try 
        {
            outlineColor = HexStringToUInt32(outlineColorStr); // Á‡‚ÂÌÛÚ¸ ‚ try catch
            fillColor = HexStringToUInt32(fillColorStr);
        }
        catch (const std::invalid_argument& e) // ‘» — ¬¿–Õ»Õ√»
        {
            std::cout << "Invalid color" << std::endl;
            return;
        }
        try
        {
            std::unique_ptr<IShape> shape = std::make_unique<CRectangle>(CPoint(startPointX, startPointY), width, height, fillColor, outlineColor);
            m_shapes.push_back(std::move(shape));
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
        
       
    };
}

void CShapesHandler::HandleCircle(std::string circleStr)
{
    std::istringstream ss(circleStr);
    std::string circleName;
    double centerPointX, centerPointY, radius;
    std::string outlineColorStr, fillColorStr;

    if (ss >> circleName >> centerPointX >> centerPointY >> radius >> fillColorStr >> outlineColorStr)

    {
        uint32_t outlineColor;
        uint32_t fillColor;
        try 
        {
            outlineColor = HexStringToUInt32(outlineColorStr);
            fillColor = HexStringToUInt32(fillColorStr);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Invalid color" << std::endl;
            return;
        }
        try {
            std::unique_ptr<IShape> shape = std::make_unique<CCircle>(CPoint(centerPointX, centerPointY), radius, fillColor, outlineColor);
            m_shapes.push_back(std::move(shape));
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    };
}

void CShapesHandler::HandleTriangle(std::string circleStr)
{
    std::istringstream ss(circleStr);
    std::string triangleName;
    double firstPointX, firstPointY, secondPointX, secondPointY, thirdPointX, thirdPointY;
    std::string outlineColorStr, fillColorStr;

    if (ss >> triangleName >> firstPointX >> firstPointY 
        >> secondPointX >>  secondPointY >> thirdPointX 
        >> thirdPointY >> fillColorStr >> outlineColorStr)
    {
        uint32_t outlineColor;
        uint32_t fillColor;
        try 
        {
            outlineColor = HexStringToUInt32(outlineColorStr);
            fillColor = HexStringToUInt32(fillColorStr);
        }
        catch(const std::invalid_argument & e)
        {
            std::cout << "Invalid color" << std::endl;
            return;
        }
        CPoint firstPoint = CPoint(firstPointX, firstPointY);
        CPoint secondPoint = CPoint(secondPointX, secondPointY);
        CPoint thirdPoint = CPoint(thirdPointX, thirdPointY);
        try {
            std::unique_ptr<IShape> shape = std::make_unique<CTriangle>(firstPoint, secondPoint, thirdPoint, fillColor, outlineColor);
            m_shapes.push_back(std::move(shape));
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    };
}

void CShapesHandler::HandleLineSegment(std::string lineSegmentStr)
{
    std::istringstream ss(lineSegmentStr);
    std::string lineSegmentName;
    double startPointX, startPointY, endPointX, endPointY;
    std::string lineColorStr;
    if (ss >> lineSegmentName >> startPointX >> startPointY
        >> endPointX >> endPointY >> lineColorStr)
    {
        uint32_t lineColor;
        try 
        {
            lineColor = HexStringToUInt32(lineColorStr);
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid color" << std::endl;
            return;
        }
            
        CPoint startPoint = CPoint(startPointX, startPointY);
        CPoint endPoint = CPoint(endPointX, endPointY);

        std::unique_ptr<IShape> shape = std::make_unique<CLineSegment>(
            startPoint,    
            endPoint,      
            lineColor     
        );
        m_shapes.push_back(std::move(shape));
        
    };
}

void CShapesHandler::HandleShape(std::string shape)
{
    std::istringstream ss(shape);
    std::string shapeType;
    ss >> shapeType;
    if (shapeType.empty())
    {
        return;
    }
    try 
    {
        Shapes shapeTyper = shapesMap.at(shapeType);
        switch (shapeTyper)
        {
            case(Shapes::rectangle):
            {
                HandleRectangle(shape);
                break;
            }
            case(Shapes::triangle):
            {
                HandleTriangle(shape);
                break;
            }
            case(Shapes::circle):
            {
                HandleCircle(shape);
                break;
            }
            case(Shapes::lineSegment):
            {
                HandleLineSegment(shape);
                break;
            }
        }
    }
    catch (std::exception e)
    {
        std::cout << "Unknown shape" << std::endl; // ÙÓÏ‡ÚËÓ‚‡ÌËÂ
    }
    
}

void CShapesHandler::HandleInputShapes()
{
    while (!m_input.eof())
    {
        std::string line;
        std::getline(m_input, line);

        try 
        {
            HandleShape(line);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
};

void CShapesHandler::DrawShapes(sf::RenderWindow& window)
{
    CCanvas canvas(window); // ¬€Õ≈—“» ¬ MAIN
    for (auto& shape : m_shapes)
    {
        shape->Draw(canvas);
    }
}	
