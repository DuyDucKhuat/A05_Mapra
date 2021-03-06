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
    DistanceGraph::NeighborT * res = new  DistanceGraph:: NeighborT(); //erstelle Obejekt, * entnehme Referenz.
    //std::unique_ptr<NeighborT> res = std::make_unique<DistanceGraph::NeighborT>(DistanceGraph::NeighborT());
    std::pair <size_t, size_t > a; // Tupelkoordinaten
    a = RowCol(v);
    if ((*this)(a.first, a.second) != CellType::Wall){
        if ( checkIndex(a.first +1, a.second))
            if ((*this)(a.first + 1, a.second) != CellType::Wall)
                res->push_back(  DistanceGraph::LocalEdgeT ((a.first + 1)*rows + a.second, 1.));
    
        if ( checkIndex(a.first -1, a.second))
            if ((*this)(a.first - 1, a.second) != CellType::Wall)
                res->push_back( DistanceGraph::LocalEdgeT ((a.first - 1)*rows + a.second, 1. ));
    
        if (checkIndex(a.first, a.second -1))
            if ((*this)(a.first, a.second -1) != CellType::Wall)
                res->push_back(DistanceGraph::LocalEdgeT ((a.first)*rows + a.second - 1, 1.));
    
        if ( checkIndex(a.first, a.second + 1))
            if ((*this)(a.first, a.second + 1) != CellType::Wall)
            {
                DistanceGraph::LocalEdgeT A((a.first)*rows + a.second + 1, 1.);
                res->push_back(A);
            }
    }
    return *res;
        
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

