//
//  MazeVisualizer.cpp
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#include "MazeVisualizer.h"


enum class VertexStatus {
    bekannt,
    unbekannt,
    optimiert
}

void MazeVisualizer::markVertex(VertexT vertex, VertexStatus status){
    
    
}
void MazeVisualizer::markEdge(EdgeT e, EdgeStatus status){}
void MazeVisualizer::updateVertex(VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) {}
void MazeVisualizer::draw() {}
