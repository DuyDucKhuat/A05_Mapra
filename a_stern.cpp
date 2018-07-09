
#include "text_visualizer.h"
#include "unit.h"
#include "CoordinateGraph.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include "MazeVisualizer.h"

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
        S[v1] = 1; //fuege v1 zu S hinzu.
	if( g.getNeighbors(v1).empty()) break;
        for ( auto v : g.getNeighbors(v1)) //aktualsiere eventuell von v1 erreichbare Knoten
            if ( D[v.first] > (D[v1] + v.second)) D[v.first] = D[v1] + v.second;
    }
    
    
}


bool A_star(const DistanceGraph& G,GraphVisualizer& V, VertexT start, VertexT ziel, std::list<VertexT>& weg) {
    // ...
    typedef DistanceGraph::LocalEdgeT LocalEdgeT;
    typedef DistanceGraph::NeighborT NeighborT;
    size_t n = G.numVertices();

    static std::vector<CostT> Weglaenge(n, infty); // Vom Startknoten aus.

    class compare { // f =  g + h;
    public:
        bool operator () (std::pair<size_t , CostT> a, std::pair<size_t , CostT> b) const {
            return  Weglaenge.at(a.first)+ a.second > Weglaenge.at(b.first) + b.second;
        }
    };

    std::vector < bool > bekannt (n,false);
    std::vector < VertexT > Vorgaenger(n, -1);
    std::vector < std::pair < VertexT, CostT > > queue ;
    std::make_heap( queue.begin(), queue.end(), compare() );

    bekannt[start] = true;
    Weglaenge[start] = 0.;
    VertexT current = start;
    EdgeT currentEdge(start,0); //########NEU
    if ( G.getNeighbors(current).empty()) return false;
    for ( auto v : G.getNeighbors(current)) { //erster Schritt: HINZUFÜGEN IN QUEUE
        Weglaenge[v.first] = v.second;
        v.second = G.estimatedCost(v.first, ziel); // ab hier ist second nur der Heuristikwert.
        queue.push_back(v);
        std::push_heap(queue.begin(), queue.end(), compare());
        //aktualisiere
        bekannt[v.first] = true;
        V.markVertex(v.first, VertexStatus::InQueue);              //########NEU
        Vorgaenger[v.first] = start;
        V.markEdge(EdgeT (start,v.first),EdgeStatus::Active);      //########NEU
    }
    while( true){
        std::pop_heap(queue.begin(),queue.end(),compare());
        current = queue.back().first;
        currentEdge.second = current;                               //########NEU
        V.markVertex( current ,VertexStatus::Active);               //########NEU
        V.markEdge( EdgeT (currentEdge.first,currentEdge.second),EdgeStatus::Visited); //########NEU
            

        //std::pop_heap(queue.begin(),queue.end(),compare());
        queue.pop_back();
        const NeighborT N = G.getNeighbors(current);

        // sind wir schon am Ziel?
        if ( current == ziel)
        {
            V.markVertex(current, VertexStatus::Destination);
            size_t w  = ziel; // backtrace für WEG
            weg.push_back(ziel);
            while (w != start){
                weg.push_back(Vorgaenger[w]);
                V.markEdge( EdgeT (Vorgaenger[w] , w),EdgeStatus::Optimal);//########NEU
                w = Vorgaenger[w];
            }
            weg.reverse();
            return true;
        }
                // evtl. neu
            // sind die neu?
        for ( auto v : N ){
            if ( !bekannt[v.first] ){
                Weglaenge[v.first] = Weglaenge[current] + v.second;
                v.second = G.estimatedCost(v.first, ziel);
                queue.push_back(v);
                std::push_heap(queue.begin(), queue.end(), compare());
                //aktualisiere Listen
                bekannt[v.first] = true;
                V.markVertex(v.first, VertexStatus::InQueue);
                Vorgaenger[v.first] = current;
                V.markEdge( EdgeT (currentEdge.second, v.first),EdgeStatus::Active);    //########NEU
                //okay, und wenn bekannt:
                //ist der neue Weg besser?
            }else if ( Weglaenge[current] + v.second < Weglaenge[v.first] ){
                Weglaenge[v.first] = Weglaenge[current] + v.second;
                Vorgaenger[v.first] = current;
                v.second = G.estimatedCost(v.first, ziel);
                queue.push_back(v);
                std::push_heap(queue.begin(), queue.end(), compare());
                
                
            }else{ // der Knoten ist bekannt, der Weg ist nicht besser, also  LÖSCHE die Möglichkeit.
                N.erase(std::remove(N.begin(), N.end(), v ), N.end()); //########NEU
            }
        }
        if(N.empty()) {V.markVertex(current, VertexStatus::Done);}//########NEU keine Möglichkeiten für diesen Knoten
        currentEdge.first = currentEdge.second; //aktualisiere Anfang.

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
int main(int argc, char * argv[])
{

    std::istringstream Istr(argv[1]);
    int bsp;
    Istr >> bsp;
    std::istringstream Istr2(argv[2]);
    int bsp2;
    Istr2 >> bsp2;
    



    if ( bsp == 1){
        
        
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
        PruefeDijkstra( 1, 0, D);
       
        std::list < VertexT > weg;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(&window, &G);

        if( A_star(G, V, 0 , 1, weg)) PruefeWeg(1,weg);
        
        
    }
    if ( bsp == 2){
        
        
        std::ifstream fin;
        fin.open("daten/Graph2.dat");
        size_t n = 0; //Anzahl der Knoten
        fin >> n;
        CoordinateGraph G(n);
        size_t edges = 0;   //Anzahl der Kanten
        fin >> edges;
        aktualsiereAdjazenz(fin, edges, G);
        std::vector<CostT> D(n,infty);
        DisplayAdjazenz(G);
        Dijkstra(G,0, D);
        PruefeDijkstra( 2, 0, D);
        
        std::list < VertexT > weg;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(&window, &G);
        if( A_star(G, V, 0, 8, weg)) PruefeWeg(2,weg);
    }
    if ( bsp == 3){
        
        
        std::ifstream fin;
        fin.open("daten/Graph3.dat");
        size_t n = 0; //Anzahl der Knoten
        fin >> n;
        CoordinateGraph G(n);
        size_t edges = 0;   //Anzahl der Kanten
        fin >> edges;
        aktualsiereAdjazenz(fin, edges, G);
        std::vector<CostT> D(n,infty);
        DisplayAdjazenz(G);
        Dijkstra(G,0, D);
        PruefeDijkstra( 3, 0, D);
        
        std::list < VertexT > weg;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G);
        if( A_star(G, V, 0, 8, weg)) PruefeWeg(3,weg);
    }
    
    if ( bsp == 4){
        

        std::ifstream fin;
        fin.open("daten/Graph4.dat");
        size_t n = 0; //Anzahl der Knoten
        fin >> n;
        CoordinateGraph G(n);
        size_t edges = 0;   //Anzahl der Kanten
        fin >> edges;
        aktualsiereAdjazenz(fin, edges, G);
        std::vector<CostT> D(n,infty);
        DisplayAdjazenz(G);
        Dijkstra(G,0, D);
        PruefeDijkstra( 4, 0, D);

        std::list < VertexT > weg;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G);
        if( A_star(G, V, 3, 8, weg)) PruefeWeg(4,weg);
    
    }
    if ( bsp == 5){

    std::ifstream fin3;
    fin3.open("daten/Maze1.dat");
    size_t breite2 = 0;
    size_t hoehe2 = 0;
    fin3 >> breite2;
    fin3 >> hoehe2;
    maze G3(breite2,hoehe2);
    readMaze(fin3, breite2, hoehe2, G3);
    
    std::list < VertexT > weg3;
    displayMaze(G3);
    std::vector < std::pair < VertexT, VertexT> > Aufgabe = StartZielPaare(5);
    std::cout << Aufgabe.size() << std::endl;
        
    sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
    MazeVisualizer V(window, G3);
    if( A_star(G3, V, Aufgabe[bsp2].first, Aufgabe[bsp2].second, weg3) ) PruefeWeg(5,weg3);
       
        
    }
    if ( bsp == 6){
        
        std::ifstream fin4;
        fin4.open("daten/Maze2.dat");
        size_t breite4 = 0;
        size_t hoehe4 = 0;
        fin4 >> breite4;
        fin4 >> hoehe4;
        maze G4(breite4,hoehe4);
        readMaze(fin4, breite4, hoehe4, G4);
        
        std::list < VertexT > weg4;
        displayMaze(G4);
        std::vector < std::pair < VertexT, VertexT> > Aufgabe = StartZielPaare(6);
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G4);
        if( A_star(G4, V, Aufgabe[bsp2].first, Aufgabe[bsp2].second, weg4))
            {
                PruefeWeg(6,weg4);
            }
    }
    if ( bsp == 7){
        
        std::ifstream fin5;
        fin5.open("daten/Maze3.dat");
        size_t breite5 = 0;
        size_t hoehe5 = 0;
        fin5 >> breite5;
        fin5 >> hoehe5;
        maze G5(breite5,hoehe5);
        readMaze(fin5, breite5, hoehe5, G5);
        
        std::list < VertexT > weg5;
        displayMaze(G5);
        std::vector < std::pair < VertexT, VertexT> > Aufgabe = StartZielPaare(7);
        std::cout << Aufgabe[bsp2].first << " "<< Aufgabe[bsp2].second << std::endl;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G5);
        if( A_star(G5, V, Aufgabe[bsp2].first, Aufgabe[bsp2].second, weg5))
        {
            PruefeWeg(7,weg5);
        }
    }
    if ( bsp == 8){
        
        std::ifstream fin5;
        fin5.open("daten/Maze4.dat");
        size_t breite5 = 0;
        size_t hoehe5 = 0;
        fin5 >> breite5;
        fin5 >> hoehe5;
        maze G5(breite5,hoehe5);
        readMaze(fin5, breite5, hoehe5, G5);
        
        std::list < VertexT > weg5;
        displayMaze(G5);
        std::vector < std::pair < VertexT, VertexT> > Aufgabe = StartZielPaare(8);
        std::cout << Aufgabe[bsp2].first << " "<< Aufgabe[bsp2].second << std::endl;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G5);
        if( A_star(G5, V, Aufgabe[bsp2].first, Aufgabe[bsp2].second, weg5))
        {
            PruefeWeg(8,weg5);
        }
    }
    if ( bsp == 9){
        
        std::ifstream fin5;
        fin5.open("daten/Maze5.dat");
        size_t breite5 = 0;
        size_t hoehe5 = 0;
        fin5 >> breite5;
        fin5 >> hoehe5;
        maze G5(breite5,hoehe5);
        readMaze(fin5, breite5, hoehe5, G5);
        
        std::list < VertexT > weg5;
        displayMaze(G5);
        std::vector < std::pair < VertexT, VertexT> > Aufgabe = StartZielPaare(9);
        std::cout << Aufgabe[bsp2].first << " "<< Aufgabe[bsp2].second << std::endl;
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G5);
        if( A_star(G5, V,Aufgabe[bsp2].first, Aufgabe[bsp2].second, weg5))
        {
            PruefeWeg(9,weg5);
        }
    }
    if ( bsp == 10){
        maze G(256,256);
        std::vector<CellType> Random = ErzeugeLabyrinth (256,256, 1);
        G.Knoten = Random;
        std::list < VertexT > weg;
        size_t start;
        size_t destination;
        for (size_t  v = 0; v < G.numVertices(); v ++){
            if( G.Knoten[v] == CellType::Destination) destination = v;
            if( G.Knoten[v] == CellType::Start) start = v;
        }
        //displayMaze(G);
        sf::RenderWindow window(sf::VideoMode(800,600), "MyWindow");
        MazeVisualizer V(window, G);
        if( A_star(G, V, start, destination , weg)){
            if ( weg.empty()) std::cout << " leer" << std::endl;
            for ( auto w : weg ) std::cout << w << " ";
            PruefeWeg(10,weg);
        }
    }
    
    
    return 0;
}
 
