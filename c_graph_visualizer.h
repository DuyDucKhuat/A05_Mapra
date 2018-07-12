//
//  c_graph_visualizer.h
//  
//
//  Created by Duc Khuat on 09.07.18.
//

#ifndef c_graph_visualizer_h
#define c_graph_visualizer_h
#include "unit.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "CoordinateGraph.h"
#include <math.h>
#include <sstream>
#include <string>

#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)

class c_graph_visualizer : public GraphVisualizer
{
    public:
    sf::RenderWindow* window;
    sf::Event* event;
    sf::Font font;
    CoordinateGraph G;
    std::vector<VertexStatus> vertex_status;
    std::vector<EdgeStatus> edge_status;
    //std::vector<CostT> Kosten;
    //std::vector<CostT> Heuristik;
    int n;
    
    
    
    c_graph_visualizer(sf::RenderWindow* w, CoordinateGraph& Graph, sf::Event* e) : event(e) {
        this->window = w;
        this->G = Graph;
        this->n = Graph.numVertices();
        this->font.loadFromFile("raleway/Raleway-Thin.ttf");

        vertex_status.resize( n, VertexStatus::UnknownVertex);
        edge_status.resize( n * n, EdgeStatus::UnknownEdge);
        //Kosten.resize(n, 0);
        //Heuristik.resize(n, 0);
    }
    ~c_graph_visualizer(){}
    void markVertex(VertexT vertex, VertexStatus status) override {this->vertex_status[vertex] = status;}
    void markEdge(EdgeT e, EdgeStatus status) override {this->edge_status[e.first*n + e.second] = status;}
    void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) override{
        //this->Kosten[vertex] = cost;
        //this->Heuristik[vertex] = estimate;
        //this->vertex_status[vertex] = status;
    }
    void draw() override;
};
#endif /* c_graph_visualizer_h */
