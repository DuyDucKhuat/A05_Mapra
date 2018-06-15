//
//  CoordinateGraph.cpp
//  
//
//  Created by Duc Khuat on 15.06.18.
//

#include "CoordinateGraph.h"

double& CoordinateGraph::operator () (size_t i, size_t j){
    return Adjazenz[i* (*this).numVertices()+j];
}
double CoordinateGraph::operator () (size_t i, size_t j){
    return Adjazenz[i* (*this).numVertices()+j];
}

NeighborT& CoordinateGraph::getNeighbors ( VertexT v){
    std::vector<LocalEdgeT> res;
    
    
    for ( int i = 0; i < (*this).numVertices(); i++){
        
        if( (*this)(v,i) != infty){
            LocalEdgeT Edge(i, (*this)(v,i));
            res.push_back(Edge);
    }
    return res;
}
    

