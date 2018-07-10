//
//  c_graph_visualizer.cpp
//  
//
//  Created by Duc Khuat on 09.07.18.
//

#include "c_graph_visualizer.h"

void c_graph_visualizer::draw(){
    bool weiter = false;

    sf::Text Kantengewicht;
    sf::Text Knoten;
    Knoten.setFont(this-> font);
    Knoten.setCharacterSize(25);
    Kantengewicht.setFont(this-> font);
    Kantengewicht.setCharacterSize(15);
    while(!weiter){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) weiter = true;

    while (this->window->pollEvent(*(this->event))){
        if(this->event->type == sf::Event::Closed)
            this->window->close();
    }
    this->window->clear(sf::Color::White);
    int Anfangsknoten = 4;  //Bsp .3 : Anfangsknoten 0, Bsp.4 Anfangsknoten z.b. 22
    double Skalierung = 140; //Bsp .3 : Skalierung 10, Bsp.4 Skalierung 50
    double x = G.Koordinaten[Anfangsknoten].first; //Mittelpunkt
    double y = G.Koordinaten[Anfangsknoten].second;
    
    //Circle
    sf::CircleShape shape(15);
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
        Knoten.setOutlineThickness(1);
        
        if(this->vertex_status[i] == VertexStatus::UnknownVertex) shape.setFillColor(sf::Color::Green);
        else if(this->vertex_status[i] == VertexStatus::InQueue) shape.setFillColor(sf::Color::Yellow);
        else if(this->vertex_status[i] == VertexStatus::Done) shape.setFillColor(sf::Color::Cyan);
        else if(this->vertex_status[i] == VertexStatus::Active) shape.setFillColor(sf::Color::Red);
        else if(this->vertex_status[i] == VertexStatus::Destination) shape.setFillColor(sf::Color::Magenta);
       //Mittelpunkt ist Anfangsknoten.
        sf::Vector2f P( 400 + Skalierung*(G.Koordinaten[i].first - x) ,300 + Skalierung*(G.Koordinaten[i].second - y));
        shape.setPosition(P);
        Knoten.setPosition(P);
        this->window->draw(shape);
        this->window->draw(Knoten);

        NeighborT N = G.getNeighbors(i);
        for (auto v :N){
            std::ostringstream strs;
            strs << v.second;
            std::string str = strs.str();
            Kantengewicht.setString( str );
            Kantengewicht.setFillColor(sf::Color::Black);
            float MittelpunktX = sf::Vector2f(shape.getPosition()).x +  0.5 * Skalierung*(G.Koordinaten[v.first].first - x);
            float MittelpunktY = sf::Vector2f(shape.getPosition()).y + 0.5 * Skalierung*(G.Koordinaten[v.first].second-y); //für das Kantengewicht
            Kantengewicht.setPosition(MittelpunktX, MittelpunktY);
            window->draw(Kantengewicht);
            if( this->edge_status[i * n + v.first] ==EdgeStatus::UnknownEdge)
            {
                sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Black),
                sf::Vertex(sf::Vector2f(400 +  Skalierung*(G.Koordinaten[v.first].first - x),300 + Skalierung*(G.Koordinaten[v.first].second-y)), sf::Color::Black) };


                window->draw(line, 2 , sf::Lines);
            }
            else if( this->edge_status[i * n + v.first] == EdgeStatus::Visited)
            {
                sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Yellow),
                sf::Vertex(sf::Vector2f(400 +  Skalierung*(G.Koordinaten[v.first].first - x),300 + Skalierung*(G.Koordinaten[v.first].second-y)), sf::Color::Yellow) };
                window->draw(line, 2 , sf::Lines);
            }
            else if( this->edge_status[i * n + v.first] ==EdgeStatus::Active)
            {
                sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Red),
                sf::Vertex(sf::Vector2f(400 +  Skalierung*(G.Koordinaten[v.first].first - x),300 + Skalierung*(G.Koordinaten[v.first].second-y)), sf::Color::Red) };
                window->draw(line, 2 , sf::Lines);
            }
            else if( this->edge_status[i * n + v.first] ==EdgeStatus::Optimal)
            {
                sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Magenta),
                sf::Vertex(sf::Vector2f(400 +  Skalierung*(G.Koordinaten[v.first].first - x),300 + Skalierung*(G.Koordinaten[v.first].second-y)), sf::Color::Magenta) };
                window->draw(line, 2 , sf::Lines);
            }
            
            
            
            
        }
    }
    window->display();
    }
}
