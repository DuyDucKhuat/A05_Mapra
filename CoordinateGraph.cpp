//
//  CoordinateGraph.cpp
//  
//
//  Created by Duc Khuat on 15.06.18.
//

#include "CoordinateGraph.h"
//###################################################################################################################
//                                              Zugriffsoperatoren
//###################################################################################################################
CostT& CoordinateGraph::operator () (size_t i, size_t j){
    return Adjazenz[i* (*this).numVertices()+j];
}

CostT CoordinateGraph::operator () (size_t i, size_t j) const{
    return Adjazenz[i* (*this).numVertices()+j];
}

//###################################################################################################################
//                                  Funktionen aus DistanceGraph
//###################################################################################################################



DistanceGraph::NeighborT & CoordinateGraph::getNeighbors  ( VertexT v) const {
    DistanceGraph::NeighborT *  res = new DistanceGraph::NeighborT();
    
    
    for ( int i = 0; i < (*this).numVertices(); i++){
        
        if( (*this)(v,i) != infty){
            DistanceGraph::LocalEdgeT Edge(i, (*this)(v,i));
            res->push_back(Edge);
   	 }
	}
    return *res;
}



CostT CoordinateGraph::estimatedCost ( VertexT from, VertexT to) const {}
CostT CoordinateGraph::cost  ( VertexT from, VertexT to) const {}




//###################################################################################################################
//                                  Testfunktionen
//###################################################################################################################

void DisplayAdjazenz ( CoordinateGraph& G){
     std:: cout <<"   ";
    for (int i = 0; i < G.numVertices() ; i++) std:: cout << i << "   ";
    std::cout << "\n";
    for (int i = 0; i < G.numVertices() ; i++) std:: cout << "_____";
    std::cout << "\n";
    
    for (int i = 0; i < G.numVertices() ; i++){
        std:: cout << i << " | ";
        for(int j = 0; j < G.numVertices(); j++) {
            if( G(i,j) != infty) std::cout << G(i,j)<< "  ";
            else std::cout << "_" << "  ";
            
        }
        std::cout<< "\n" ;
    }

}


int main()
{
    std::ifstream fin;
    fin.open("daten/Graph2.dat");
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

    DisplayAdjazenz(G);
    return 0;
    
}
 

