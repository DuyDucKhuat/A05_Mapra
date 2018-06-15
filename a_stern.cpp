
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

bool allTrue( vector <int> S){
    for( int i = 0; i < S.size() ; i++) if (S[i] ==0) return false;
    return true;
}
int minIndex( vector< CostT> D){
    int res = 0;
    CostT min = infty;
    for ( int i = 0; i < D.size(); i++) if (D[i]< min && D[i]!=0 ) res = i;
    return i;
}
//#########################################################################################################

void Dijkstra(const DistanceGraph& g, GraphVisualizer& v, VertexT start, std::vector<CostT>& kostenZumStart) {
    // ...
    size_t n =g.numVertices();

    vector< size_t > S(n,0) ;
    vector< double > D(n,infty);
    D[start] = 0;
    S[start] = 1;
    //erste Schleife
    for ( int i = 0; i < n ; i++)
        if( i != start)
            D[i] = g(start,i);
    while( !(allTrue(S)))
    {
        size_t v1 = minIndex(D);
        S[v1] = 1; //fuege v1 zu S hinzu.
        for ( int i = 0; i < n ; i ++)  if ( S[i] == 0)
                                        if( (D[v1]+g(v1,i)) < D[i])
                                            D[i] := D[v1]+g(v1,i);
    }
    
    
    
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
 
