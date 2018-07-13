//
//  c_graph_visualizer.cpp
//  
//
//  Created by Duc Khuat on 09.07.18.
//

#include "c_graph_visualizer.h"

void c_graph_visualizer::draw(){
    bool weiter = false;
    int hoehe = this->window->getSize().x;// TODOOOOO
    int breite = this->window->getSize().y;
    sf::Text Kantengewicht;
    sf::Text Knoten;
    //sf::Text Heuristik;
    Knoten.setFont(this-> font);
    Kantengewicht.setFont(this-> font);
    //Heuristik.setFont( this-> font);
    
    while(!weiter){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) weiter = true;

    while (this->window->pollEvent(*(this->event))){
        if(this->event->type == sf::Event::Closed)
            this->window->close();
    }
        this->window->clear(sf::Color::White); // BSP 2: Anfangsknoten 4, Skalierung 190
        
    // ######################################## ANPASSUNGEN
    /*int Anfangsknoten = 9;  //Bsp .3 : 9, Bsp.4 : 7
    double Skalierung = 18; //Bsp .3 : 8, Bsp.4 97  | Breite Hoehe 1000, 1000
    double SkalierungText = 0.85 ; // Bsp.3 :  0.85 Bsp.4 : 0.17 ,
    double SkalierungDreieck = 0.5; // Bsp.3: 0.5 */

    Knoten.setCharacterSize(15); // 25 1-3, 10 für 4 ###################################
    Kantengewicht.setCharacterSize(15); // this->Skalierung * this->SkalierungText
    //Heuristik.setCharacterSize(this->Skalierung * this->SkalierungText);

    //###############################################
    double x = G.Koordinaten[Mittelpunkt].first; //Mittelpunkt
    double y = G.Koordinaten[Mittelpunkt].second;
    
    //Circle
    sf::CircleShape shape(10); // 15 für 1-3 , 10 für
    shape.setOutlineThickness(0.1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    for ( int i  = 0 ; i < n ; i ++){
        std::ostringstream strs;
        strs << i;
        std::string str = strs.str();
        Knoten.setString( str );
        Knoten.setFillColor( sf::Color::Black);
        Knoten.setOutlineColor( sf::Color::Black);
        Knoten.setOutlineThickness( 0.2 ); //1 , 1-3  0.2 4
        if(this->vertex_status[i] == VertexStatus::UnknownVertex) shape.setFillColor(sf::Color::Green);
        else if(this->vertex_status[i] == VertexStatus::InQueue) shape.setFillColor(sf::Color::Yellow);
        else if(this->vertex_status[i] == VertexStatus::Done) shape.setFillColor(sf::Color::Cyan);
        else if(this->vertex_status[i] == VertexStatus::Active) shape.setFillColor(sf::Color::Red);
        else if(this->vertex_status[i] == VertexStatus::Destination) shape.setFillColor(sf::Color::Magenta);
       //Mittelpunkt ist Anfangsknoten.
        sf::Vector2f P( hoehe/2. + this->Skalierung*(G.Koordinaten[i].first - x) ,breite/2. + this->Skalierung*(G.Koordinaten[i].second - y));
        shape.setPosition(P);
        Knoten.setPosition(P);
        this->window->draw(shape);
        this->window->draw(Knoten);

        NeighborT N = G.getNeighbors(i);
        for (auto v :N){
            sf::CircleShape triangle(9,3); //10 für 1-3 this->Skalierung * this-> SkalierungDreieck
            triangle.setOrigin(triangle.getRadius(),triangle.getRadius());

            sf::Vector2f P2(hoehe/2. +  this->Skalierung*(G.Koordinaten[v.first].first - x), breite/2. + this->Skalierung*(G.Koordinaten[v.first].second-y));
            std::ostringstream strs;
            strs << v.second;
            std::string str = strs.str();
            Kantengewicht.setString( str );
            Kantengewicht.setFillColor(sf::Color(10,200,100));
            Kantengewicht.setOutlineThickness( 0.1); //this->Skalierung * this->SkalierungText

            //Drehwinkel
            double X = P2.x - P.x;
            double Y = P2.y - P.y;
            double alpha = acos (X / sqrt(X*X +Y*Y)) * 360;
            alpha /= (acos(-1)*2);
            triangle.setPosition(sf::Vector2f((P.x + P2.x)/2.,(P.y + P2.y)/2.));
            triangle.setRotation(30 + alpha);
            Kantengewicht.setPosition(sf::Vector2f((P.x + P2.x)/2. + 5, (P.y + P2.y)/2.));
            
            if( this->edge_status[i * n + v.first] ==EdgeStatus::UnknownEdge)
            {
                sf::Vertex line[] ={sf::Vertex(P, sf::Color::Black),
                    sf::Vertex(P2, sf::Color::Black) };
                triangle.setFillColor(sf::Color::Black);
                Kantengewicht.setOutlineColor( sf::Color::Black);

                window->draw(line, 2, sf::Lines);
            }
            else if( this->edge_status[i * n + v.first] == EdgeStatus::Visited)
            {
                sf::Vertex line[] ={sf::Vertex(P, sf::Color::Yellow),
                sf::Vertex(P2, sf::Color::Yellow) };
                window->draw(line, 2 , sf::Lines);
                triangle.setFillColor(sf::Color::Yellow);

                Kantengewicht.setOutlineColor( sf::Color::Yellow);

            }
            else if( this->edge_status[i * n + v.first] ==EdgeStatus::Active)
            {
                sf::Vertex line[] ={sf::Vertex(P, sf::Color::Red),
                sf::Vertex(P2, sf::Color::Red) };
                window->draw(line, 2 , sf::Lines);
                triangle.setFillColor(sf::Color::Red);

                Kantengewicht.setOutlineColor( sf::Color::Red);

            }
            else if( this->edge_status[i * n + v.first] ==EdgeStatus::Optimal)
            {
                sf::Vertex line[] ={sf::Vertex(P, sf::Color::Magenta),
                sf::Vertex(P2, sf::Color::Magenta) };
                window->draw(line, 2 , sf::Lines);
                triangle.setFillColor(sf::Color::Magenta);
                Kantengewicht.setOutlineColor( sf::Color::Magenta);

            }
            window->draw(Kantengewicht);
            window->draw(triangle);
            
            
        }
    }
    window->display();
    }
}
