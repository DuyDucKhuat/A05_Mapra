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
#include <fstream>
#include <math.h>


class maze : public DistanceGraph
{
    public:
    //links oben ist der erste Knoten, rechts unten der letzte.
    std::vector< CellType > Knoten;
    size_t rows;
    size_t cols;
    

    maze (size_t breite = 0, size_t hoehe = 0) : DistanceGraph(breite*hoehe), rows(hoehe), cols(breite){
        
        Knoten.resize(breite*hoehe, CellType::Wall);
    }
    ~maze();
    NeighborT& getNeighbors( VertexT v) const;
    CostT estimatedCost ( VertexT from, VertexT to) const;
    CostT cost ( VertexT from, VertexT to) const {return 1.;}
    
    
    
    
    //Hilfsfunktionen
    std::pair <size_t, size_t> RowCol(VertexT v) const { return std::pair <size_t, size_t> (v/ rows, v % rows);}
    bool checkIndex ( size_t i, size_t j) const;
    
    // Zugriffsoperatoren
    CellType&operator () (size_t i, size_t j){return Knoten[i*rows+j];}
    CellType operator () (size_t i, size_t j) const {return Knoten[i*rows +j];}
    
    

};

#endif /* maze_h */
