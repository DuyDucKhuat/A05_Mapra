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
#include <fstream>

#define CoordinateGraph_h

  //  	typedef std::pair<VertexT, CostT> LocalEdgeT;

//	typedef std::vector<LocalEdgeT> NeighborT;
class CoordinateGraph : public DistanceGraph
{
    public:
    std::vector<CostT> Adjazenz;                        // Adjazenzmatrix des Graphen mit Kosten.
    std::vector< std::pair<double,double>> Koordinaten; //enthält die Koordinaten der Knoten.
    

    CoordinateGraph (size_t num_verts = 0 ) : DistanceGraph(num_verts) {Adjazenz.resize(num_verts*num_verts, infty); Koordinaten.resize(num_verts, std::vector(2,0) );}
    CostT& operator () (size_t i, size_t j);
    CostT operator () (size_t i, size_t j) const ;
    NeighborT & getNeighbors ( VertexT v) const;
    CostT estimatedCost ( VertexT from, VertexT to) const;
    CostT cost ( VertexT from, VertexT to) const;
    
    
    

};
#endif /* CoordinateGraph_h */
