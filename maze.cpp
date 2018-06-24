//
//  maze.cpp
//  
//
//  Created by Duc Khuat on 22.06.18.
//

#include "maze.h"
bool maze::checkIndex ( size_t i, size_t j) const {  //gültiger Index?
    size_t k = 0;
    k--;
    return (i != k) && (i < rows) && (j !=k) && (j < cols) ;
}

DistanceGraph::NeighborT& maze::getNeighbors (VertexT v) const {
    DistanceGraph::NeighborT * res = new DistanceGraph:: NeighborT(); //erstelle Obejekt, * entnehme Referenz.
    std::pair <size_t, size_t > a; // Tupelkoordinaten
    a = RowCol(v);
    
    if ( checkIndex(a.first +1, a.second)) res->push_back(  *((*this)(a.first + 1, a.second)) );
    if ( checkIndex(a.first -1, a.second))res->push_back( (*this)(a.first - 1, a.second) );
    if ( checkIndex(a.first, a.second -1))res->push_back((*this)(a.first, a.second -1)):
    if ( checkIndex(a.first, a.second + 1))res->push_back((*this)(a.first, a.second +1)):
        return res;
        
}

CostT maze::estimatedCost( VertexT from, VertexT to) const // 1-Norm von a-b.
{
    std::pair <size_t, size_t > a = RowCol(from);
    std::pair <size_t, size_t > b = RowCol(to);
    if ( a.first > b.first){
        
        if (a.second > b.second) return a.first-b.first + a.second - b.second;
        else return a.first -b.first + b.second - a.second;
    }else{
        if (a.second > b.second) return b.first -a.first + a.second -b.second;
        else return b.first -a.first + b.second -a.second;
    }
}

