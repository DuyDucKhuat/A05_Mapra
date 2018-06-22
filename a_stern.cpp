
#include "text_visualizer.h"
#include "unit.h"
#include "CoordinateGraph.h"

// Ein Graph, der Koordinaten von Knoten speichert.
/*class CoordinateGraph : public DistanceGraph {
public:
    const NeighborT& getNeighbors( VertexT v) const override;
    
    CostT estimatedCost( VertexT from, VertexT to) const override;
    
    CostT cost( VertexT from, VertexT to) const override;
};*/
//#########################################################################################################
//                              Hilfsfunktionen
//#########################################################################################################

bool allTrue( std::vector < size_t > S){
    for( int i = 0; i < S.size() ; i++) if (S[i] ==0) return false;
    return true;
}
int minIndex( std::vector< CostT> D, std::vector <size_t> S){
    int res = 0;
    CostT min = infty;
    for ( int i = 0; i < D.size(); i++)
    {
        if (D[i]< min && D[i]!=0  && S[i] == 0){
            min = D[i];
            res = i;
        }
    }
    return res;
}
//#########################################################################################################

void Dijkstra(const DistanceGraph& g, VertexT start, std::vector<CostT>& kostenZumStart) {
    // ...
    size_t n = g.numVertices();

    std::vector< size_t > S(n,0) ;
    std::vector< double > D(n,infty);
    D[start] = 0;
    S[start] = 1;
    //erste Schleife
    NeighborT T = g.getNeighbors(start);
    for ( auto element : T ) std::cout << element.first << " ";

    for ( auto v : g.getNeighbors(start))
        D[v.first] = v.second;

    while( !(allTrue(S)))
    {
        //for ( auto element : S) std::cout << element << " ";
        //std::cout << "\n" << std::endl;
        //for ( auto element : D) std::cout << element << " ";
        //std::cout << "\n" << std::endl;


        size_t v1 = minIndex(D,S);
        S[v1] = 1; //fuege v1 zu S hinzu.
        for ( auto v : g.getNeighbors(v1)) //aktualsiere eventuell von v1 erreichbare Knoten
            if ( D[v.first] > (D[v1] + v.second)) D[v.first] = D[v1] + v.second;
    }
    
    
}

bool A_star(const DistanceGraph& g, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
    // ...
    return false; // Kein Weg gefunden.
}


void aktualsiereAdjazenz( std::ifstream& in , size_t edges, CoordinateGraph G){
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
    // Frage Beispielnummer vom User ab
    std::ifstream fin;
    fin.open("daten/Graph4.dat");
    size_t n = 0; //Anzahl der Knoten
    fin >> n;
    CoordinateGraph G(n);
    size_t edges = 0;   //Anzahl der Kanten
    fin >> edges;
    aktualsiereAdjazenz(fin, edges, G);
    std::vector<CostT> D(n,infty);
    Dijkstra(G,0, D);
    PruefeDijkstra( 4, 0, D);
    // Lade die zugehoerige Textdatei in einen Graphen
    // PruefeHeuristik
    
    // Loese die in der Aufgabenstellung beschriebenen Probleme fuer die jeweilige Datei
    // PruefeDijkstra / PruefeWeg
    
    return 0;
    // TODO: 16.Juni. Der beschissene Scheiß funktioniert nicht. Ich kann die funktionen aus meiner CoordinateGraph Klasse nicht hier benutzen. Das heißt rüberkopieren und schauen ob es hier geht.
    // hart unnötig :D
}
 
