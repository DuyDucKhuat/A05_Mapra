//
//  c_graph_visualizer.cpp
//  
//
//  Created by Duc Khuat on 09.07.18.
//

#include "c_graph_visualizer.h"

void c_graph_visualizer::draw(sf::Color::White){
    this->window->clear();
    //Circle
    sf::CircleShape shape(20);
    shape.setFillColor(sf::Color(50, 50,30));
    shape.setOutlineThickness(0.5);
    shape.setOutlineColor(sf::Color(250,150,100));
    
    for ( int i  = 0 ; i < n ; i ++){
        if(this->vertex_status[i] == VertexStatus::UnknownVertex) shape.setFillColor(sf::Color::Green);
        else if(this->vertex_status[i] == VertexStatus::InQueue) shape.setFillColor(sf::Color::Yellow);
        else if(this->vertex_status[i] == VertexStatus::Done) shape.setFillColor(sf::Color::Cyan);
        else if(this->vertex_status[i] == VertexStatus::Active) shape.setFillColor(sf::Color::Red);
        else if(this->vertex_status[i] == VertexStatus::Destination) shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(400+ G.Koordinaten[i].first, 300 + G.Koordinaten[i].second);
        this->window->draw(shape);
    }
    //for (int i = 0; i < n * n, i++){
        
    //}
    
}
