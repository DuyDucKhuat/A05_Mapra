//
//  MazeVisualizer.cpp
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#include "MazeVisualizer.h"

void MazeVisualizer::markVertex(VertexT vertex, VertexStatus status){}
void MazeVisualizer::markEdge(EdgeT e, EdgeStatus status){}
void MazeVisualizer::updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) {}
void MazeVisualizer::draw() {}

int main (){
    /*MazeVisualizer test(80,60);
    while ((test.window).isOpen())
    {
        sf::Event event;
        while((test.window).pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                test.window.close();
        }
        for (sf::Vector2f x : test.vertices ){
            test.window.clear();
            sf::RectangleShape rec( sf::Vector2f(test.widthRec,test.heightRec)  );
            rec.setFillColor (BLUE);
            rec.setOutlineThickness(1);
            rec.setOutlineColor (BLACK);
            rec.setPosition(x);
            test.window.draw(rec);
            test.window.display();
        }
    }*/
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
        
        // start the current frame: clear the window with black color
        window.clear();
        
        // defines a circle
        sf::CircleShape shape(200);
        
        // set the shape color to green
        shape.setFillColor(sf::Color(50, 50, 30));
        
        shape.setOutlineThickness(1); // creates an outline around the circle
        shape.setOutlineColor(sf::Color(250, 150, 100)); // outline color is orange
        
        // The coordinates, which can be used to set the position of a circle are by default the top left corner of the
        // smallest square containing the circle. Using setOrigin, we can move these coordinates to the center of the circle.
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        
        //sets the (absolute) position of the circle, (0,0) is the top-left corner.
        shape.setPosition(0,0); // positioning the circle 200 units right from the top left corner
        
        window.draw(shape); // draws the shape, a green circle with an orange outline
        
        
        window.draw(shape); // draws the shape, another green circle with an orange outline
        
        // defines a line between the position of the circle and the coordinates (800,600)
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(shape.getPosition())),
            sf::Vertex(sf::Vector2f(800,600))
        };
        
        for (int i = 0; i < 10 ; i ++){
            sf::RectangleShape rect (sf::Vector2f(80,60));
            rect.setFillColor(sf::Color::Blue);
            rect.setOutlineThickness(1);
            rect.setOutlineColor(sf::Color::Red);
            rect.setPosition(80*i, 0 );
            window.draw( rect);
            
            
        }
        
        
        window.draw(line, 2, sf::Lines); //draws the line
        
        
        
        
        
        // end the current frame
        window.display();
        
    }
    return 0 ;
}
