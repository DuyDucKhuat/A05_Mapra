//
//  MazeVisualizer.cpp
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#include "MazeVisualizer.h"


void MazeVisualizer::markVertex(VertexT vertex, VertexStatus status) override {this->vertex_status[vertex] = status;}
//##############################################################################################################

void MazeVisualizer::markEdge(EdgeT e, EdgeStatus status) override {}
//##############################################################################################################

void MazeVisualizer::updateVertex (VertexT vertex,  double cost, double estimate, VertexT parent, VertexStatus status) override
{}

//##############################################################################################################
void MazeVisualizer::draw() override {
    sf::Event event;
    while(this->window->pollEvent(event)){
        if(event.type== sf::Event::Closed)
            this->window->close();
    }
    this->window->clear();
    //Rechteck
    sf::Vector2f v(widthRec, heightRec);
    sf::RectangleShape rect(v);
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::White);
    fori(this->maze->rows){ //aktualsiere Feld;
        forj(this->maze->cols){
            if(maze(i,j) == CellType::Wall) rect.setFillColor(sf::Color::Blue);
            else if(vertex_status[i*(this->maze->rows)+j] == VertexStatus::UnknownVertex) rect.setFillColor(sf::Color::Green);
            else if(vertex_status[i*(this->maze->rows)+j] == VertexStatus::InQueue) rect.setFillColor(sf::Color::Yellow);
            else if(vertex_status[i*(this->maze->rows)+j] == VertexStatus::Done) rect.setFillColor(sf::Color::Cyan);
            else if(vertex_status[i*(this->maze->rows)+j] == VertexStatus::Active) rect.setFillColor(sf::Color::Red);
            else if(vertex_status[i*(this->maze->rows)+j] == VertexStatus::Destination) rect.setFillColor(sf::Color::Magenta);
            rect.setPosition(i*widhtRec, j*heightRec);
            this->window->draw(rect);
        }
    }
    this->window->display();
}

int main (){
    MazeVisualizer test(80,60);
    

    return 0 ;
}













/*sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
 
 // run the program as long as the window is open
 while (window.isOpen())
 {
 sf::Event event;
 while (window.pollEvent(event)) // event loop
 {
 if (event.type == sf::Event::Closed)
 window.close();
 }
 window.clear();
 sf::CircleShape shape(200);
 shape.setFillColor(sf::Color(50, 50, 30));
 shape.setOutlineThickness(1); // creates an outline around the circle
 shape.setOutlineColor(sf::Color(250, 150, 100)); // outline color is orange
 shape.setOrigin(shape.getRadius(), shape.getRadius());
 shape.setPosition(0,0); // positioning the circle 200 units right from the top left corner
 window.draw(shape); // draws the shape, a green circle with an orange outline
 window.display();
 }*/
