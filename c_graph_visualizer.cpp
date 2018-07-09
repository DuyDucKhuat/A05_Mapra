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
    //Circle
    sf::CircleShape shape(5);
    shape.setOutlineThickness(0.5);
    shape.setOutlineColor(sf::Color::Black);
    
    for ( int i  = 0 ; i < n ; i ++){
        if(this->vertex_status[i] == VertexStatus::UnknownVertex) shape.setFillColor(sf::Color::Green);
        else if(this->vertex_status[i] == VertexStatus::InQueue) shape.setFillColor(sf::Color::Yellow);
        else if(this->vertex_status[i] == VertexStatus::Done) shape.setFillColor(sf::Color::Cyan);
        else if(this->vertex_status[i] == VertexStatus::Active) shape.setFillColor(sf::Color::Red);
        else if(this->vertex_status[i] == VertexStatus::Destination) shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(800 - 20*G.Koordinaten[i].first, 20*G.Koordinaten[i].second);
        this->window->draw(shape);
        NeighborT N = G.getNeighbors(i);
        for (auto v :N){
            sf::Vertex line[] ={sf::Vertex(sf::Vector2f(shape.getPosition()), sf::Color::Magenta),
            sf::Vertex(sf::Vector2f(800 - 20 * G.Koordinaten[v.first].first,20 * G.Koordinaten[v.first].second), sf::Color::Magenta) };
            window->draw(line, 2 , sf::Lines);
        }
    }
    window->display();
}
