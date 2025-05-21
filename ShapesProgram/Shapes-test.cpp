#define CATCH_CONFIG_MAIN

#include <SFML/Graphics.hpp>
#include "catch.hpp"
#include "fakeit.hpp"
#include <math.h>
#include <iostream>
#include "IShape.h"
#include "ISolidShape.h"
#include "CShapesHandler.h"
#include "CPoint.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include <numbers>


const double PI = std::numbers::pi;

namespace
{
constexpr double invalidRadius = -10.2;

constexpr uint32_t outlineColor = 0xffffff;
constexpr uint32_t fillColor = 0xababab;
constexpr double width = 100.0;
constexpr double height = 50.0;
constexpr double validRadius = 25.0;
constexpr double triangleArea = 6.0;
constexpr double trianglePerimetr = 12;


CPoint firstPoint = CPoint{ 3.0, 0.0 };
CPoint secondPoint = CPoint{ 0.0, 4.0 };
CPoint thirdPoint = CPoint{ 0.0, 0.0 };

CPoint invalidFirstPoint = CPoint{ 0.0, 0.0 };
CPoint invalidSecondPoint = CPoint{ 0.0, 4.0 };
CPoint invalidThirdPoint = CPoint{ 0.0, 0.0 };
}

TEST_CASE("Circle tests")
{
	CCircle circle(firstPoint, validRadius, fillColor, outlineColor);
	CHECK(circle.GetCenter().GetX() == firstPoint.GetX());
	CHECK(circle.GetCenter().GetY() == firstPoint.GetY());

	CHECK(circle.GetArea() == (validRadius * PI * validRadius));
	CHECK(circle.GetPerimeter() == (2 * PI * validRadius));

	CHECK(circle.GetFillColor() == fillColor);
	CHECK(circle.GetOutlineColor() == outlineColor);
}

TEST_CASE("Rectangle tests")
{
	CRectangle rect(firstPoint, width, height, fillColor, outlineColor);
	CHECK(rect.GetLeftTop().GetX() == firstPoint.GetX());
	CHECK(rect.GetLeftTop().GetY() == firstPoint.GetY());

	CHECK(rect.GetRightBottom().GetX() == rect.GetLeftTop().GetX() + width);
	CHECK(rect.GetRightBottom().GetY() == rect.GetLeftTop().GetY() - height);

	CHECK(rect.GetHeight() == height);
	CHECK(rect.GetWidth() == width);

	CHECK(rect.GetArea() == height * width);
	CHECK(rect.GetPerimeter() == 2 * (height + width));

	CHECK(rect.GetFillColor() == fillColor);
	CHECK(rect.GetOutlineColor() == outlineColor);
}

TEST_CASE("Line tests")
{
	CLineSegment line(firstPoint, secondPoint, outlineColor);

	CHECK(line.GetArea() == 0);
	CHECK(line.GetStartPoint().GetX() == firstPoint.GetX());
	CHECK(line.GetStartPoint().GetY() == firstPoint.GetY());

	CHECK(line.GetEndPoint().GetX() == secondPoint.GetX());
	CHECK(line.GetEndPoint().GetY() == secondPoint.GetY());

	CHECK(line.GetPerimeter() == firstPoint.GetDistanceToPoint(secondPoint));

	CHECK(line.GetOutlineColor() == outlineColor);
}

TEST_CASE("Triangle tests")
{
	CTriangle triangle(firstPoint, secondPoint, thirdPoint, fillColor, outlineColor);

	CHECK(triangle.GetVertex1().GetX() == firstPoint.GetX());
	CHECK(triangle.GetVertex1().GetY() == firstPoint.GetY());

	CHECK(triangle.GetVertex2().GetX() == secondPoint.GetX());
	CHECK(triangle.GetVertex2().GetY() == secondPoint.GetY());

	CHECK(triangle.GetVertex3().GetX() == thirdPoint.GetX());
	CHECK(triangle.GetVertex3().GetY() == thirdPoint.GetY());

	CHECK(triangle.GetArea() == triangleArea);
	CHECK(triangle.GetPerimeter() == trianglePerimetr);

	CHECK(triangle.GetFillColor() == fillColor);
	CHECK(triangle.GetOutlineColor() == outlineColor);

	CHECK_THROWS_AS(CTriangle(invalidFirstPoint, invalidSecondPoint, invalidThirdPoint, fillColor, outlineColor), std::invalid_argument);
}
TEST_CASE("ShapesHandler test")
{
	std::stringstream ss;
	ss << "rectangle 10.3 20.15 30.7 40.4 ff0000ff 00ff00ff\n" << "circle 3.0 25.0 00ff00ff 00ff00ff\n" 
		<< "triangle 3.0 0.0 0.0 4.0 0.0 0.0 00ff00ff 00ff00ff\n" << "lineSegment 0.0 10.0 00ff00ff\n";
	CShapesHandler shapesHandler(ss, std::cout);
	shapesHandler.HandleInputShapes();
	shapesHandler.PrintShapesInfo(); //доработать проверять тчо приходит
}
// Проверяем, что Draw вызовет FillCircle с нужными аргументами
TEST_CASE("Circle drawing test")
{
	fakeit::Mock<ICanvas> mock;
	ICanvas& canvas = mock.get();

	CCircle circle(CPoint(100, 100), 25, 0xFFFF00, 0x000000);

	SECTION("Verify drawing calls")
	{
		fakeit::When(Method(mock, FillCircle)).Return();

		circle.Draw(canvas);

		fakeit::Verify(Method(mock, FillCircle)
			.Using(CPoint(100, 100), 25.0, 0xFFFF00, 0x000000)
		).Once();
	}

	SECTION("Test with invalid radius")
	{
		CHECK_THROWS_AS(
			CCircle(CPoint(0, 0), -10, 0xFF, 0xFF),
			std::invalid_argument
		);
	}
}

TEST_CASE("Drawing tests")
{
	fakeit::Mock<ICanvas> mock;
	ICanvas& canvas = mock.get();
	CRectangle rectangle(CPoint(100, 100), 150, 150, 0xFFF0FFFF, 0x000000FF);
	CTriangle triangle(CPoint(100, 100), CPoint(150, 150), CPoint(100, 200), 0xFFF0FFFF, 0x000000FF);
	CCircle circle(CPoint(100, 100), 25, 0xFFFF00FF, 0x000000FF);
	CLineSegment line(CPoint(100, 100), CPoint(200, 100), 0x000000FF);

	SECTION("Verify drawing calls CIRCLE") // CIRCLE
	{
		fakeit::When(Method(mock, FillCircle)).Return();

		circle.Draw(canvas);

		fakeit::Verify(Method(mock, FillCircle)
			.Using(CPoint(100, 100), 25.0, 0xFFFF00FF, 0x000000FF)
		).Once();
	}

	SECTION("Verify drawing calls RECTANGLE") // RECTANGLE
	{
		fakeit::When(Method(mock, FillRect)).Return();

		rectangle.Draw(canvas);
		fakeit::Verify(Method(mock, FillRect).Using(CPoint(100, 100), 150, 150, 0xFFF0FFFF, 0x000000FF)).Once();
	}
	SECTION("Verify drawing calls TRIANGLE") { // TRIANGLE
		std::vector<CPoint> actualPoints;
		std::vector<CPoint> expectedPoints = {
			CPoint(100, 100),
			CPoint(150, 150),
			CPoint(100, 200)
		};
		uint32_t actualFill = 0;
		uint32_t actualOutline = 0;
	
		fakeit::When(Method(mock, FillPolygon)).Do([&](const std::vector<CPoint>& points, uint32_t fill, uint32_t outline) {
			actualPoints = points;
			actualFill = fill;
			actualOutline = outline;
			});

		triangle.Draw(canvas);

		CHECK(actualFill == 0xFFF0FFFF);
		CHECK(actualOutline == 0x000000FF);

		CHECK(actualPoints.size() == expectedPoints.size());

		CHECK(expectedPoints == actualPoints);
		
	}
	SECTION("Verify drawing calls LineSegment") // LINESEGMENT
	{
		fakeit::When(Method(mock, DrawLine)).Return();

		line.Draw(canvas);
		fakeit::Verify(Method(mock, DrawLine).Using(CPoint(100, 100), CPoint(200, 100), 0x000000FF)).Once();
	}
}