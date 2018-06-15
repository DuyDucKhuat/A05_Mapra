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
//Euklidische Norm. "Luftlinie"
CostT CoordinateGraph::estimatedCost ( VertexT from, VertexT to) const {
    CostT res = (Koordinaten[from].first - Koordinaten[to].first)*(Koordinaten[from].first - Koordinaten[to].first);
    res =+ (Koordinaten[from].second-Koordinaten[to].second)*(Koordinaten[from].second-Koordinaten[to].second);
    return sqrt(res);
}





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
    //Lese die Koordinaten der Knoten ein. Pro Knoten ein Tupel (x,y).
    for (int i = 0; i < G.numVertices() ; i++){
        in >> G.Koordinaten[i].first;
        in >> G.Koordinaten[i].second;
    }
}


int main()
{
    std::ifstream fin;
    fin.open("daten/Graph5.dat");
    size_t n = 0; //Anzahl der Knoten
    fin >> n;
    CoordinateGraph G(n);
    size_t edges = 0;   //Anzahl der Kanten
    fin >> edges;
    
    aktualsiereAdjazenz(fin, G, edges);
    std::cout <<G.estimatedCost(0,2) << std::endl;

    DisplayAdjazenz(G);
    std::cout << PruefeHeuristik(G) << std::endl;
    return 0;
    
}
 

