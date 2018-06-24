//
//  maze.h
//  
//
//  Created by Duc Khuat on 22.06.18.
//

#ifndef maze_h
#define maze_h
#include "unit.h"
#include <vector>
#include <iostream>
#include <math.h>


class maze : public DistanceGraph
{
    public:
    std::vector< std::pair < CellType, DistanceGraph::NeighborT> > Knoten;
    size_t rows;
    size_t cols;
    

    maze (size_t breite = 0, size_t hoehe = 0) : DistanceGraph(breite*hoehe), rows(hoehe), cols(breite){
        DistanceGraph::NeighborT v ;
        Knoten.resize(breite*hoehe, std::pair < CellType, DistanceGraph::NeigborT > (CellType::Wall, v));
    }
    NeighborT& getNeighbors( VertexT v) const;
    CostT estimatedCost ( VertexT from, VertexT to) const;
    CostT cost ( VertexT from, VertexT to) const {return 1.;}
    
    
    
    
    //Hilfsfunktionen
    std::pair <size_t, size_t> RowCol(VertexT ){ return std::pair <size_t, size_t> (v/ rows, v % rows);}
    bool checkIndex ( size_t i, size_t j);
    
    // Zugriffsoperatoren
    std::pair < CellType, DistanceGraph::NeighborT> &operator () (size_t i, size_t j){return Knoten[i*rows+j];}
    std::pair < CellType, DistanceGraph::NeighborT> operator () (size_t i, size_t j) const {return Knoten[i*rows +j];}
    
    

};

#endif /* maze_h */
