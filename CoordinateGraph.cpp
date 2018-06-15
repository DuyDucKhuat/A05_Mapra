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


// Gibt die Nachbarknoten eines gegebenen Knotens v zurueck.

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


// Heuristik: Schaetzt die Kosten, um vom Knoten "from" zum Knoten "to" zu gelangen.
CostT CoordinateGraph::estimatedCost ( VertexT from, VertexT to) const {
    
}



// Gibt die wahren Kosten c an, um vom Knoten "from" zum Knoten "to" zu gelangen.
// Existiert zwischen den beiden Knoten keine Kante, werden die Kosten mit infty bewertet.
CostT CoordinateGraph::cost  ( VertexT from, VertexT to) const {}




//###################################################################################################################
//                                  Testfunktionen
//###################################################################################################################

void DisplayAdjazenz ( CoordinateGraph& G){
     std:: cout <<"    ";
    for (int i = 0; i < G.numVertices() ; i++) std:: cout << i << "  ";
    std::cout << "\n";
    for (int i = 0; i < G.numVertices() ; i++) std:: cout << "____";
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

//Lese die Kanten mit Kantengewichten ab.
void aktualsiereAdjazenz( std::ifstream& in , CoordinateGraph& G, size_t edges){
    size_t i, j ;
    CostT wert = infty;
    for (int l = 0; l < edges; l++)
    {
        in >> i;
        in >> j;
        in >> wert;
        G(i,j) = wert;
    }
    G.Koordinaten.resize(G.numVertices(),std::pair(0,0));
    for (int i = 0; i < G.numVertices() ; i++){
        in >> G.Koordinaten[i].first;
        in >> G.Koordinaten[i].second;
    }
    std::cout << G.Koordinaten[0].second << std::endl;
}


int main()
{
    std::ifstream fin;
    fin.open("daten/Graph2.dat");
    size_t n = 0; //Anzahl der Knoten
    fin >> n;
    CoordinateGraph G(n);
    size_t edges = 0;   //Anzahl der Kanten
    fin >> edges;
    
    aktualsiereAdjazenz(fin, G, edges);


    DisplayAdjazenz(G);
    return 0;
    
}
 

