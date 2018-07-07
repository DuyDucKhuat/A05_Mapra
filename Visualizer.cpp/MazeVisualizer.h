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
#include <vector>
#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)
#define vector std::vector
#define POS sf::Vector2f
#define BREITE 800
#define HOEHE 600
#define REC sf::RectangleShape
#define GREY sf::Color::Grey
#define BLACK sf::Color::Black



class MazeVisualizer : public GraphVisualizer
{
    public:
        sf::RenderWindow window;
        vector < POS > vertices;
        size_t rows;
        size_t cols;
        double widthRec;
        double heigthRec;
    
    
        MazeVisualizer(size_t r, size_t c) : window(sf::VideoMode(BREITE, HOEHE), "My window"),
                                             rows(r),
                                             cols(c),
                                             widhtRec( BREITE./c),
                                             heightRec( HOEHE./r)
        {
            vertices.resize(r*c);
            fori(rows){
                forj(cols){
                    POS vertex(j*widthRec, i*heightRec);
                    (*this)(i,j) = vertex;
                }
            }
            for ( POS x : vertices ){
                REC rec( POS(widthRec,heightRec)  );
                rec.setFillColor (GREY);
                rec.setOutlineThickness(1);
                rec.setOutlineColor (BLACK);
                rec.setPosition(x);
                window.draw(rec);
            }
        }
    
        ~GraphVisualizer() {}
        void markVertex(VertexT vertex, VertexStatus status){}
        void markEdge(EdgeT e, EdgeStatus status){}
        void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) {}
        void draw() {}
    
        sf::Vector2f& operator () (size_t i, size_t j){return vertices[i*rows+j];}
        sf::Vector2f operator () (size_t i, size_t j){return vertices[i*rows+j];}


};

#endif /* MazeVisualizer_h */
