#include <SFML/Graphics.hpp>
class TestVisualizer {
public:
    sf::RenderWindow window;
    TestVisualizer () : window( sf::VideoMode(800,600), "My window") {}
    
};
int main() {
    TestVisualizer test;
    while (test.window.isOpen())
    {
        sf::Event event;
        while(test.window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                test.window.close();
        }
        
    }
    test.window.clear(sf::Color::Black);
    test.window.display();
    

}
