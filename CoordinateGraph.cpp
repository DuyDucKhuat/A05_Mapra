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

DistanceGraph::NeighborT & CoordinateGraph::getNeighbors ( VertexT v){
    DistanceGraph::NeighborT *  res = new DistanceGraph::NeighborT();
    
    
    for ( int i = 0; i < (*this).numVertices(); i++){
        
        if( (*this)(v,i) != infty){
            DistanceGraph::LocalEdgeT Edge(i, (*this)(v,i));
            res->push_back(Edge);
   	 }
	}
    return *res;
}


istream& operator >> (istream& in, CoordinateGraph& G)
{
    
    
}

int main()
{
    std::ifstream fin;
    fin.open("daten/Graph1.dat");
    size_t n = 0; //Anzahl der Knoten
    fin >> n;
    CoordinateGraph G(n);
    size_t edges = 0;
    fin >> edges;
    for ( int l = 0 ; l < edges ; l++){
        size_t i,j;
        CostT wert = infty;
        fin >> i;
        fin >> j;
        fin >> wert;
        G(i,j) = wert;
    }
    return 0;
    
}
 

