//
//  CoordinateGraph.cpp
//  
//
//  Created by Duc Khuat on 15.06.18.
//

#include "CoordinateGraph.h"

CostT& CoordinateGraph::operator () (size_t i, size_t j){
    return Adjazenz[i* (*this).numVertices()+j];
}
//CostT CoordinateGraph::operator () (size_t i, size_t j){
 //   return Adjazenz[i* (*this).numVertices()+j];
//}

NeighborT& CoordinateGraph::getNeighbors ( VertexT v){
    NeighborT *  res = new NeighborT();
    
    
    for ( int i = 0; i < (*this).numVertices(); i++){
        
        if( (*this)(v,i) != infty){
            LocalEdgeT Edge(i, (*this)(v,i));
            res.push_back(Edge);
    }
    return &res;
}
    

