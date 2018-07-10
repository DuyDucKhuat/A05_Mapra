
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    
    // run the program as long as the window is open
    while (window.isOpen())
    {

        
            // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) // event loop
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        sf::Font font;
        font.loadFromFile("../../raleway/Raleway-Thin.ttf");
        if ( !font.loadFromFile ( "../../raleway/Raleway-Thin.ttf" )) {
            std::cout << " Error loading file" << std::endl;
            system ("pause");
        }
        sf::Text text;
        text.setFont(font);
        text.setString ( "hi");
        window.draw(text);
        // start the current frame: clear the window with black color
        
        // defines a circle
        sf::CircleShape shape(100);
        sf::CircleShape triangle(50,3);
        triangle.setOrigin(triangle.getRadius(),triangle.getRadius());
        triangle.setPosition(400,300);
        //triangle.setOrigin(triangle.getRadius(),triangle.getRadius());
        double alpha = asin( 600 / 800);
        alpha = (alpha *360) / acos(-1);
        triangle.setRotation(alpha);

        // set the shape color to green
        shape.setFillColor(sf::Color(100, 250, 50));
        
        shape.setOutlineThickness(10); // creates an outline around the circle
        shape.setOutlineColor(sf::Color(250, 150, 100)); // outline color is orange
        
        // The coordinates, which can be used to set the position of a circle are by default the top left corner of the
        // smallest square containing the circle. Using setOrigin, we can move these coordinates to the center of the circle.
        //shape.setPosition(400,300);
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        
        //sets the (absolute) position of the circle, (0,0) is the top-left corner.
        //shape.setPosition(200,0); // positioning the circle 200 units right from the top left corner
        
        //window.draw(shape); // draws the shape, a green circle with an orange outline
        
        //shape.move(0,300); // moves the position 300 units down from the previous position (-> circle is drawn at (200,300))
        
        window.draw(shape); // draws the shape, another green circle with an orange outline
        
        // defines a line between the position of the circle and the coordinates (800,600)
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(shape.getPosition())),
            sf::Vertex(sf::Vector2f(800,600))
        };
        window.draw(triangle);
        window.draw(line, 2, sf::Lines); //draws the line
        
        // Before working on the visualizer for your A*-algorithm, try to draw your own stuff here!
        // For instance:
        
        // - Use the font given in Font/BebasNeue-Regular.ttf to create texts
        // - Add different shapes and sprites and figure out more transforming entities
        
        // See https://www.sfml-dev.org/tutorials/2.5/#graphics-module for a good tutorial!
        
        
        // end the current frame
        window.display();
    }
    
    
    return 0;
}
