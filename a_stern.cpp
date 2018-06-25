
#include "text_visualizer.h"
#include "unit.h"
#include "CoordinateGraph.h"
#include "maze.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>


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
//                          GRAPHALGORITHMEN
//#########################################################################################################


void Dijkstra(const DistanceGraph& g, VertexT start, std::vector<CostT>& D) {
    // ...
    size_t n = g.numVertices();

    std::vector< size_t > S(n,0) ;
    D[start] = 0;
    S[start] = 1;
    //erste Schleife
    for ( auto v : g.getNeighbors(start))
        D[v.first] = v.second;
    while( !(allTrue(S)) )
    {
        size_t v1 = minIndex(D,S);
	if( g.getNeighbors(v1).empty()) break;
        S[v1] = 1; //fuege v1 zu S hinzu.
        for ( auto v : g.getNeighbors(v1)) //aktualsiere eventuell von v1 erreichbare Knoten
            if ( D[v.first] > (D[v1] + v.second)) D[v.first] = D[v1] + v.second;
    }
    
    
}

bool A_star(const DistanceGraph& G, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
    // ...
    typedef DistanceGraph::LocalEdgeT LocalEdgeT;
    typedef DistanceGraph::NeighborT NeighborT;
    size_t n = G.numVertices();
    static std::vector<CostT> Weglaenge(n, infty); // Vom Startknoten aus.

    class compare { // f =  g + h;
    public:
        bool operator () (std::pair<size_t , CostT> a, std::pair<size_t , CostT> b) const {
            std::cout << a.first << " " << b.first << std::endl;
            std::cout << " f Werte : " << Weglaenge[a.first]+ a.second << " " <<  Weglaenge[b.first] + b.second << std::endl;
            return  Weglaenge[a.first]+ a.second > Weglaenge[b.first] + b.second;
        }
    };
    
    std::vector < bool > bekannt (n,false);
    std::vector < VertexT > Vorgaenger(n, -1);
    std::vector < std::pair < VertexT, CostT > > queue ; //

        std::make_heap( queue.begin(), queue.end(), compare() );

        bekannt[start] = true;
        Weglaenge[start] = 0.;
        VertexT current = start;
    for ( auto v : G.getNeighbors(current)) std::cout << v.first << std::endl;
        for ( auto v : G.getNeighbors(current)) {
            v.second = G.estimatedCost(v.first, ziel);
            std::cout << "hier" << v.first << " " << v.second << std::endl;
            queue.push_back(v);
            std::push_heap(queue.begin(), queue.end(), compare());

            Weglaenge[v.first] = v.second;
            std::cout << "hier2" << " " << Weglaenge[v.first] << std::endl;
            bekannt[v.first] = true;
            Vorgaenger[v.first] = start;
        }

        while( true){
            std::pop_heap(queue.begin(),queue.end(),compare());
            VertexT current = queue.back().first;
            std::cout << current << std::endl;

            queue.pop_back();


            
            NeighborT Nodes = G.getNeighbors(current);          // evtl. neu

            // sind die neu?
            
            for ( auto v : Nodes){
                if ( !bekannt[v.first] ){
                    // sind wir schon am Ziel?
                    if ( v.first == ziel)
                    {
                        size_t w  = ziel;
                        weg.push_back(ziel);
                        while (w != start){
                            weg.push_back(Vorgaenger[w]);
                            w = Vorgaenger[w];
                            for( auto v : weg) std::cout << v << std::endl;

                        }
                        return true;
                    }
                    v.second = G.estimatedCost(v.first, ziel);
                    queue.push_back(v);
                    std::pop_heap(queue.begin(), queue.end(), compare());
                    bekannt[v.first] = true;
                    Weglaenge[v.first] = Weglaenge[current] + v.second;
                    Vorgaenger[v.first] = current;
                        
                //okay, und wenn bekannt:
                //ist der neue Weg besser?
                }else if ( Weglaenge[current] + v.second < Weglaenge[v.first] ){
                    Weglaenge[v.first] = Weglaenge[current] + v.second;
                    Vorgaenger[v.first] = current;
                }
            }
            if( queue.empty()) return false;
        }
    return false; // Kein Weg gefunden.
}
//############################################################################################################
//                           COORDINATEGRAPH
//############################################################################################################

void aktualsiereAdjazenz( std::ifstream& in , size_t edges, CoordinateGraph& G){
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

//############################################################################################################
//                           MAZE
//############################################################################################################

void readMaze( std::ifstream& in , size_t rows, size_t cols, maze& G){
    char s;
    for ( int i = 0; i < rows ; i++){
        for( int j = 0; j < cols ; j ++){
            in >> s;
            if( s =='.') G(i,j)= CellType::Ground;
        }
    }
}
void displayMaze (maze& G)
{
    for ( int i = 0 ; i < G.rows; i ++){
        for ( int j = 0; j < G.cols ; j++){
            if( G(i,j) == CellType::Wall) std::cout << "#" << " ";
            else std::cout << "."  << " ";
        } std::cout << "\n";
    }
}
//############################################################################################################
//                          MAIN
//############################################################################################################
int main()
{
    // Frage Beispielnummer vom User ab
    std::ifstream fin;
    fin.open("daten/Graph1.dat");
    size_t n = 0; //Anzahl der Knoten
    fin >> n;
    CoordinateGraph G(n);
    size_t edges = 0;   //Anzahl der Kanten
    fin >> edges;
    aktualsiereAdjazenz(fin, edges, G);
    std::vector<CostT> D(n,infty);
    DisplayAdjazenz(G);
    Dijkstra(G,0, D);
    //PruefeDijkstra( 1, 0, D);
    
    std::list<VertexT> weg;
    if(A_star(G, 0, 2, weg)) std::cout << " hi" << std::endl;
    PruefeWeg(1, weg);
    for( auto v : weg) std::cout << v << std::endl;
    
    fin.close();
    // Lade die zugehoerige Textdatei in einen Graphen
    // PruefeHeuristik
    
    std::ifstream fin2;
    fin2.open("daten/Maze2.dat");
    size_t breite = 0;
    size_t hoehe = 0;
    fin2 >> breite;
    fin2 >> hoehe;
    maze G2(breite,hoehe);
    readMaze(fin2, breite, hoehe, G2);
    std::vector<CostT> D2(breite*hoehe,infty);
    displayMaze(G2);
    Dijkstra(G2,9,D2);
    for ( auto v : D2) std::cout << v << " ";
    std::cout << "\n" ;
    
    //PruefeDijkstra(5, 9, D2);
    
    
    // Loese die in der Aufgabenstellung beschriebenen Probleme fuer die jeweilige Datei
    // PruefeDijkstra / PruefeWeg
    
    return 0;
}
 
