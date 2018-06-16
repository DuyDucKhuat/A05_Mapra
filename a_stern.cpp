
#include "text_visualizer.h"
#include "unit.h"

// Ein Graph, der Koordinaten von Knoten speichert.
class CoordinateGraph : public DistanceGraph {
public:
    const NeighborT& getNeighbors( VertexT v) const override;
    
    CostT estimatedCost( VertexT from, VertexT to) const override;
    
    CostT cost( VertexT from, VertexT to) const override;
};
//#########################################################################################################
//                              Hilfsfunktionen
//#########################################################################################################

bool allTrue( std::vector < size_t > S){
    for( int i = 0; i < S.size() ; i++) if (S[i] ==0) return false;
    return true;
}
int minIndex( std::vector< CostT> D){
    int res = 0;
    CostT min = infty;
    for ( int i = 0; i < D.size(); i++) if (D[i]< min && D[i]!=0 ) res = i;
    return res;
}
//#########################################################################################################

void Dijkstra(const DistanceGraph& g, GraphVisualizer& v, VertexT start, std::vector<CostT>& kostenZumStart) {
    // ...
    size_t n =g.numVertices();

    std::vector< size_t > S(n,0) ;
    std::vector< double > D(n,infty);
    D[start] = 0;
    S[start] = 1;
    //erste Schleife
    for ( auto v : g.getNeighbors(start))
        D[v.first] = v.second;
    while( !(allTrue(S)))
    {
        size_t v1 = minIndex(D);
        S[v1] = 1; //fuege v1 zu S hinzu.
        for ( auto v : g.getNeighbors(v1))
            if ( D[v.first] > (D[v1] + v.second)) D[v.first] = D[v1] + v.second;

    }
    
    
    //TODO : Wechsle von g(i,j) auf die Verwendung von getNeighborT
}

bool A_star(const DistanceGraph& g, GraphVisualizer& v, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
    // ...
    return false; // Kein Weg gefunden.
}

int main()
{
    // Frage Beispielnummer vom User ab
    
    // Lade die zugehoerige Textdatei in einen Graphen
    // PruefeHeuristik
    
    // Loese die in der Aufgabenstellung beschriebenen Probleme fuer die jeweilige Datei
    // PruefeDijkstra / PruefeWeg
    
    return 0;
}
 
