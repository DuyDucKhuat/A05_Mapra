//
//  MazeVisualizer.cpp
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#include "MazeVisualizer.h"
typedef MazeVisualizer::markVertex          markVertex;
typedef MazeVisualizer::markEdge            markEdge;
typedef MazeVisualizer::updateVertex        updateVertex;
typedef MazeVisualizer::draw                draw;


void markVertex(VertexT vertex, VertexStatus status){
    
    
}
void markEdge(EdgeT e, EdgeStatus status){}
void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) {}
void draw() {}

int main (){
    MazeVisualizer test(20,30);
    while(test.window.isOpen())
    {
        sf::Event event;
        while(test.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                test.window.close();
        }
        test.window.display();
    }
