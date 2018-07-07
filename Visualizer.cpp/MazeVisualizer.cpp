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
    MazeVisualizer test(80,60);
    
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
    return 0 ;
}
