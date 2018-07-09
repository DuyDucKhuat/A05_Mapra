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
    
    c_graph_visualizer(sf::RenderWindow* w, CoordinateGraph& Graph) window(w), G(Graph){}
    ~c_graph_visualizer(){}
    void markVertex(VertexT vertex, VertexStatus status) override;
    void markEdge(EdgeT e, EdgeStatus status) override;
    void updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status)override;
    void draw() override;
};
#endif /* c_graph_visualizer_h */
