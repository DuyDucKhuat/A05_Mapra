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
#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)

#define BLUE sf::Color::Blue
#define BLACK sf::Color::Black



class MazeVisualizer : public GraphVisualizer
{
    public:
        sf::RenderWindow window;
        std::vector < POS > vertices;
        size_t rows;
        size_t cols;
        double widthRec;
        double heigthRec;
    
    
        MazeVisualizer(size_t r, size_t c) : window(sf::VideoMode(BREITE, HOEHE), "My window"),
                                             rows(r),
                                             cols(c),
        {
            widthRec = 800./c;
            heightRec = 600./r;
            vertices.resize(r*c);
            fori(rows){
                forj(cols){
                    sf::Vector2f vertex(j*widthRec, i*heightRec);
                    (*this)(i,j) = vertex;
                }
            }
            for (sf::Vector2f x : vertices ){
                sf::RectangleShape rec( sf::Vector2f(widthRec,heightRec)  );
                rec.setFillColor (BLUE);
                rec.setOutlineThickness(1);
                rec.setOutlineColor (BLACK);
                rec.setPosition(x);
                window.draw(rec);
            }
        }
    
        ~MazeVisualizer() {}
        void markVertex(VertexT vertex, VertexStatus status);
        void markEdge(EdgeT e, EdgeStatus status);
        void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status);
        void draw();
    
        sf::Vector2f& operator () (size_t i, size_t j){return vertices[i*rows+j];}
        sf::Vector2f operator () (size_t i, size_t j){return vertices[i*rows+j];}


};

#endif /* MazeVisualizer_h */
