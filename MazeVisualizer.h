//
//  MazeVisualizer.h
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#ifndef MazeVisualizer_h
#define MazeVisualizer_h
#include "unit.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "maze.h"
#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)




class MazeVisualizer : public GraphVisualizer
{
    public:
        sf::RenderWindow* window;
        sf::Event* event;
        maze m;
        std::vector<VertexStatus> vertex_status;
        double widthRec;
        double heightRec;

    
    
    
    MazeVisualizer(sf::RenderWindow* window1, maze& m1 , sf::Event* e) :m(m1), event(e)
        {
            this->window = window1;
            this->widthRec = 800./(this->m.cols);
            this->heightRec = 600./(this->m.rows);
            vertex_status.resize( this->m.numVertices(), VertexStatus::UnknownVertex);
        }
        ~MazeVisualizer() {}
        void markVertex(VertexT vertex, VertexStatus status) override {this->vertex_status[vertex] = status;}
        void markEdge(EdgeT e, EdgeStatus status) override {}
        void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status)override {}
        void draw() override;
    
            


};

#endif /* MazeVisualizer_h */
