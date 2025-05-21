#include "CShapesHandler.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

const int WIDTH = 800;
const int HEIGHT = 600;
const std::string TITLE = "ShapesProgram";

void ProcessWindow(sf::RenderWindow& window)
{
    std::ifstream inputFile("test-data/house.txt");
    std::istream& input = inputFile;
    std::ostream& output = std::cout;

    bool endOfInput = false;

    CShapesHandler shapesHandler(input, output);

    while (window.isOpen())
    {
        sf::Event event = {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!endOfInput)
        {
            shapesHandler.HandleInputShapes();
            if (input.eof())
            {
                endOfInput = true;
                shapesHandler.PrintShapesInfo();
            }
        }


        window.clear(sf::Color::White);

        shapesHandler.DrawShapes(window);

        window.display();
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
    
    ProcessWindow(window);

    return 0;
}
