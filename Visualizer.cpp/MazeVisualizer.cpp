//
//  MazeVisualizer.cpp
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#include "MazeVisualizer.h"

void MazeVisualizer::markVertex(VertexT vertex, VertexStatus status) override {}
void MazeVisualizer::markEdge(EdgeT e, EdgeStatus status) override {}
void MazeVisualizer::updateVertex (VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) override
{
    this->status[vertex]= status;
    
    
}
void MazeVisualizer::draw() override {}

int main (){
    MazeVisualizer test(80,60);
    

    return 0 ;
}













/*sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
 
 // run the program as long as the window is open
 while (window.isOpen())
 {
 sf::Event event;
 while (window.pollEvent(event)) // event loop
 {
 if (event.type == sf::Event::Closed)
 window.close();
 }
 window.clear();
 sf::CircleShape shape(200);
 shape.setFillColor(sf::Color(50, 50, 30));
 shape.setOutlineThickness(1); // creates an outline around the circle
 shape.setOutlineColor(sf::Color(250, 150, 100)); // outline color is orange
 shape.setOrigin(shape.getRadius(), shape.getRadius());
 shape.setPosition(0,0); // positioning the circle 200 units right from the top left corner
 window.draw(shape); // draws the shape, a green circle with an orange outline
 window.display();
 }*/
