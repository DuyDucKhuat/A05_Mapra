//
//  CoordinateGraph.h
//  
//
//  Created by Duc Khuat on 15.06.18.
//

#ifndef CoordinateGraph_h
#include "unit.h"
#include <vector>
#include <iostream>

#define CoordinateGraph_h
class CoordinateGraph : public DistanceGraph
{
    public:
    std::vector<CostT> Adjazenz;
    
    
    CoordinateGraph (size_t num_verts = 0 ) : DistanceGraph(num_verts) {Adjazenz.resize(num_verts*num_verts, infty);}
    CostT& operator () (size_t i, size_t j);
   // CostT operator () (size_t i, size_t j) ;
    NeighborT getNeighbors ( VertexT v);

};
#endif /* CoordinateGraph_h */
