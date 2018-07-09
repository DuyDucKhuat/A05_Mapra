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
#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)

class c_graph_visualizer : public GraphVisualizer
{
    public:
    sf::RenderWindow* window;
    CoordinateGraph G;
    std::vector<VertexStatus> vertex_status;
    std::vector<EdgeStatus> edge_status;
    int n;
    
    
    c_graph_visualizer(sf::RenderWindow* w, CoordinateGraph& Graph) {
        this->window = w;
        this->G = Graph;
        this->n = Graph.numVertices();
        vertex_status.resize( n, VertexStatus::UnknownVertex);
        edge_status.resize( n*n, EdgeStatus::UnknownEdge);
    }
    ~c_graph_visualizer(){}
    void markVertex(VertexT vertex, VertexStatus status) override{this->vertex_status[vertex] = status;}
    void markEdge(EdgeT e, EdgeStatus status) override{this->edge_status[e.first*(this->n)+e.second] = status;}
    void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) override;
    void draw() override;
};
#endif /* c_graph_visualizer_h */
