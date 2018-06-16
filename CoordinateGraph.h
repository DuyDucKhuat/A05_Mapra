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
#include <math.h>

#define CoordinateGraph_h

  //  	typedef std::pair<VertexT, CostT> LocalEdgeT;

//	typedef std::vector<LocalEdgeT> NeighborT;
class CoordinateGraph : public DistanceGraph
{
    public:
    std::vector<CostT> Adjazenz;                        // Adjazenzmatrix des Graphen mit Kosten.
    std::vector< std::pair<double,double> > Koordinaten; //enthält die Koordinaten der Knoten, als Tupel (x,y).
    

    CoordinateGraph (size_t num_verts = 0 ) : DistanceGraph(num_verts)
    {
        
        Adjazenz.resize(num_verts*num_verts, infty);
        std::pair<double, double> a(0,0);
        Koordinaten.resize(num_verts, a);
    }
    CostT& operator () (size_t i, size_t j);
    CostT operator () (size_t i, size_t j) const ;
    NeighborT & getNeighbors ( VertexT v) const;
    CostT estimatedCost ( VertexT from, VertexT to) const;
    CostT cost ( VertexT from, VertexT to) const{return (*this)(from,to);}
    void aktualsiereAdjazenz( std::ifstream& in , CoordinateGraph& G, size_t edges);
    
    

};
#endif /* CoordinateGraph_h */
