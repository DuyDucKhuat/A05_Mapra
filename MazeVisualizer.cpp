//
//  MazeVisualizer.cpp
//  
//
//  Created by Duc Khuat on 06.07.18.
//

#include "MazeVisualizer.h"


//##############################################################################################################
void MazeVisualizer::draw() {
    
    while(this->window->pollEvent(*(this->event))){
        if(this->event->type== sf::Event::Closed)
            this->window->close();
    }
    this->window->clear();
    //Rechteck
    sf::Vector2f v(widthRec, heightRec);
    sf::RectangleShape rect(v);
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(0.1);
    rect.setOutlineColor(sf::Color::White);


    for(int i = 0 ; i <this->m.rows; i++){ //aktualsiere Feld;
        for(int j = 0; j < this->m.cols; j++){
            if(this->m.Knoten[i*this->m.cols+j] == CellType::Wall) rect.setFillColor(sf::Color::Blue);

            else if(vertex_status[i*(this->m.cols)+j] == VertexStatus::UnknownVertex) rect.setFillColor(sf::Color::Green);
            else if(vertex_status[i*(this->m.cols)+j] == VertexStatus::InQueue) rect.setFillColor(sf::Color::Yellow);
            else if(vertex_status[i*(this->m.cols)+j] == VertexStatus::Done) rect.setFillColor(sf::Color::Cyan);
            else if(vertex_status[i*(this->m.cols)+j] == VertexStatus::Active) rect.setFillColor(sf::Color::Red);
            else if(vertex_status[i*(this->m.cols)+j] == VertexStatus::Destination) rect.setFillColor(sf::Color::Magenta);
            rect.setPosition(i*this->widthRec, j*this->heightRec);
            this->window->draw(rect);
        }
    }
    this->window->display();

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
