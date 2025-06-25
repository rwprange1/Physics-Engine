#include "Display.h"



Display::Display(){
    this->videoMode = sf::VideoMode({1000, 800});
    this->window = sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);

    this->buildObjects();


    
}

/**
 * This function will check to see if the window is still open
 * that is the game is still running
 * returns a bool on if the game is running still
 */
bool Display::isWinOpen(){
    return this->window.isOpen();
}

void Display::render(){
    this->window.clear();

    for (auto &e: this->objects){
        this->window.draw(e);
        //std::cout << e.getPosition().x << " " << e.getPosition().y <<"\n";
    }


    this->window.display();
}

void Display::update(){
    this->pollEvents();
}

/** 
 * wh
 */
void Display::pollEvents(){
    //event polling
    while(const std::optional event = this->window.pollEvent()){
        
        if (event ->is<sf::Event::Closed>()){
            window.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            const sf::Keyboard::Scancode key = keyPressed->scancode;

            switch(key){
                case sf::Keyboard::Scancode::Escape:
                    std::cout << "Escape Was Hit" << std::endl;
                    window.close();
                    break;
                case sf::Keyboard::Scancode::Space:
                    std::cout << "Space Was Hit" << std::endl;  
                    break;  
            }

            
        }
    }
}

/**
 * Spawn in 1,000 trhough 10,000 little circles which will turn into projectiles and place them randomly on the screen
 * !todo(make sure collisions prevent cirlces spawning on one another)
 * 
 * @returns void
 */
void Display::buildObjects(){
    std::vector<sf::Color> colors = {sf::Color::Blue,sf::Color::Green, sf::Color::Red, sf::Color::Magenta};


    int numObjects = (1 + rand()) % 10;
    for (int i = 0; i < numObjects; i++) {
        int color =  (1 + rand()) % 4; 
        sf::CircleShape circle; 
        
        circle.setRadius(25.f);
        //create a function which returns a random position not contained in the list, and not causing collisons

        circle.setPosition(sf::Vector2f(
            rand() % static_cast<int>(this->window.getSize().x - circle.getRadius()),
            rand() % static_cast<int>(this->window.getSize().y - circle.getRadius())
        ));

        std::cout << "Color: " + std::to_string(color) << std::endl;
        circle.setFillColor(colors[color]);

        this->objects.push_back(circle);
    }

    std::cout << "Generated " + std::to_string(numObjects) << " balls :)\n";

}