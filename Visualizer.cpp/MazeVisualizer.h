//
//  MazeVisualizer.h
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#ifndef MazeVisualizer_h
#define MazeVisualizer_h
#include "../unit.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)

#define BLUE sf::Color::Blue
#define BLACK sf::Color::Black



class MazeVisualizer : public GraphVisualizer
{
    public:
        sf::RenderWindow window;
        Maze maze;
        std::vector<VertexStatus> vertex_status;
        double widthRec;
        double heightRec;

    
    
    
    MazeVisualizer(sf::RenderWindow window, Maze& maze ) : window(sf::VideoMode(800, 600), "My window"),
                                             window(window),
                                             maze(maze)
        {
            this->widthRec = 800./(maze->cols);
            this->heightRec = 600./(maze->rows);
            vertex_status.resize(maze.numVertices(), VertexStatus::UnknownVertex);
        }
        ~MazeVisualizer() {}
        void markVertex(VertexT vertex, VertexStatus status) override;e
        void markEdge(EdgeT e, EdgeStatus status) override;
        void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status)override;
        void draw() override;
    
            
        //Hilfsoperator
        sf::Vector2f& operator () (size_t i, size_t j){return status[i*rows+j];}


};

#endif /* MazeVisualizer_h */
