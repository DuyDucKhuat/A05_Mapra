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
    std::cout << test.widthRec << " " << test.heigthRec << std::endl;
    return 0 ;
}
