//
//  MazeVisualizer.h
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#ifndef MazeVisualizer_h
#define MazeVisualizer_h
#include "unit.h"
#include < SFML/Graphics.hpp>

class MazeVisualizer : public GraphVisualizer
{
    public:
        sf::RenderWindow window;
        MazeVisualizer() : window(sf::VideoMode(800,600), "My window") {}
        ~GraphVisualizer() {}
        void markVertex(VertexT vertex, VertexStatus status){}
        void markEdge(EdgeT e, EdgeStatus status){}
        void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) {}
        void draw() {}

};

#endif /* MazeVisualizer_h */
