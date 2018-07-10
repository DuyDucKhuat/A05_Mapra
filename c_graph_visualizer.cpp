//
//  c_graph_visualizer.cpp
//  
//
//  Created by Duc Khuat on 09.07.18.
//

#include "c_graph_visualizer.h"

void c_graph_visualizer::draw(){
    while (this->window->pollEvent(*(this->event))){
        if(this->event->type == sf::Event::Closed)
            this->window->close();
    }
    this->window->clear(sf::Color::White);
    int Anfangsknoten = 0;
    double Skalierung = 15;
    double x = G.Koordinaten[Anfangsknoten].first; //Mittelpunkt
    double y = G.Koordinaten[Anfangsknoten].second;
    
    //Circle
    sf::CircleShape shape(15);
    shape.setOutlineThickness(0.1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    //erster Knoten
    if(this->vertex_status[Anfangsknoten] == VertexStatus::UnknownVertex) shape.setFillColor(sf::Color::Green);
    else if(this->vertex_status[Anfangsknoten] == VertexStatus::InQueue) shape.setFillColor(sf::Color::Yellow);
    else if(this->vertex_status[Anfangsknoten] == VertexStatus::Done) shape.setFillColor(sf::Color::Cyan);
    else if(this->vertex_status[Anfangsknoten] == VertexStatus::Active) shape.setFillColor(sf::Color::Red);
    else if(this->vertex_status[Anfangsknoten] == VertexStatus::Destination) shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(400,300);
    this->window->draw(shape);

    NeighborT N = G.getNeighbors(0);
    for (auto v :N){
        sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Black),
            sf::Vertex(sf::Vector2f(400 + Skalierung*(G.Koordinaten[v.first].first - x) , 300+ Skalierung*(G.Koordinaten[v.first].second - y)), sf::Color::Black) };
        window->draw(line, 2 , sf::Lines);
    }
    for ( int i  = 1 ; i < n ; i ++){
        if(this->vertex_status[i] == VertexStatus::UnknownVertex) shape.setFillColor(sf::Color::Green);
        else if(this->vertex_status[i] == VertexStatus::InQueue) shape.setFillColor(sf::Color::Yellow);
        else if(this->vertex_status[i] == VertexStatus::Done) shape.setFillColor(sf::Color::Cyan);
        else if(this->vertex_status[i] == VertexStatus::Active) shape.setFillColor(sf::Color::Red);
        else if(this->vertex_status[i] == VertexStatus::Destination) shape.setFillColor(sf::Color::Magenta);
        
        shape.setPosition( 400 + Skalierung*(G.Koordinaten[i].first - x) ,300 + Skalierung*(G.Koordinaten[i].second - y) );
        this->window->draw(shape);
        NeighborT N = G.getNeighbors(i);
        for (auto v :N){
            sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Black),
            sf::Vertex(sf::Vector2f(400 +  Skalierung*(G.Koordinaten[v.first].first - x),300 + Skalierung*(G.Koordinaten[v.first].second-y)), sf::Color::Black) };
            window->draw(line, 2 , sf::Lines);
        }
    }
    window->display();
}
