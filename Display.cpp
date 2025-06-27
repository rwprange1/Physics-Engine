#include "Display.h"


/**
 * The 
 */
Display::Display(){
    this->videoMode = sf::VideoMode({1000, 800});
    this->window = sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(0);

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

/**
 * Draws all of the objects to the screen
 * @returns void
 */
void Display::render(){
    this->window.clear();

  
    
    for (auto &e: this->objects){
        this->window.draw(std::get<0>(e));
    }


    this->window.display();
}

void Display::update(){
    this->pollEvents();


    this->updateObjects();
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
    std::vector<sf::Color> colors = {sf::Color::Blue,sf::Color::Green, sf::Color::Red, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Yellow};

    int numObjects = 300 + (rand() % 10);
    //int numObjects = 50;
    for (int i = 0; i < numObjects; i++) {
        int color =  (1 + rand()) % 6; 
        sf::CircleShape circle; 
        
        circle.setRadius(5.f);
        //create a function which returns a random position not contained in the list, and not causing collisons

        sf::Vector2f pos = sf::Vector2f(
            rand() % static_cast<int>(this->window.getSize().x - circle.getRadius()),
            rand() % static_cast<int>(this->window.getSize().y - circle.getRadius())
        );
        circle.setPosition(pos);
        
        while (!this->validatePos(circle)){
            sf::Vector2f pos = sf::Vector2f(
            rand() % static_cast<int>(this->window.getSize().x - circle.getRadius()),
            rand() % static_cast<int>(this->window.getSize().y - circle.getRadius())
            );
            circle.setPosition(pos);
        }
        
        circle.setFillColor(colors[color]);

        this->objects.push_back(std::make_tuple(circle, this->makeVec(circle) ));
    }
    std::cout << "Generated " + std::to_string(numObjects) << " balls :)\n";
}



/**
 * Generate a random vector of floats
 * @returns a vector2f of random 2 values
 */
sf::Vector2f Display::makeVec(sf::CircleShape circle){
    return sf::Vector2f(
            -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.f))),
            -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.f)))
        );
}


/**
 * This function will handle the collision detection, and move the objects accordingly
 * 
 */
void Display::updateObjects(){

    for (auto &e1: this->objects){
        std::get<0>(e1).move(std::get<1>(e1));
        int posX = std::get<0>(e1).getPosition().x;
        int posY = std::get<0>(e1).getPosition().y;
        if ( posX < 0 || posX > (this->window.getSize().x -  2 * std::get<0>(e1).getRadius())){
            std::get<1>(e1).x = std::get<1>(e1).x * -1.f;
        }

        if ( posY < 0 || posY > (this->window.getSize().y - 2 * std::get<0>(e1).getRadius())){
            std::get<1>(e1).y = std::get<1>(e1).y * -1.f;
        }

        for (auto &e2: this->objects){
            if (&std::get<0>(e1) != &std::get<0>(e2) && this->isCollisionWithBall(std::get<0>(e1),std::get<0>(e2))) {
                sf::Vector2f v1 = std::get<1>(e1); 
                sf::Vector2f v2 = std::get<1>(e2); 

                sf::Vector2f temp = v2;
                std::get<1>(e2) = v1;
                std::get<1>(e1) = temp; 
            }
        }
    }



}



bool Display::isCollisionWithBall(sf::CircleShape c1, sf::CircleShape c2){
    sf::Vector2f c1Point = c1.getPosition();
    sf::Vector2f c2Point = c2.getPosition();
    
    float a = std::abs( c1Point.x - c2Point.x);
    float b = std::abs( c1Point.y - c2Point.y);
    float diff = a*a + b*b;

    return diff <= (c1.getRadius() + c2.getRadius()) * (c1.getRadius() + c2.getRadius());

}

/**
 * On spawn of balls make sure none are in invalid positions
 * @returns bol, false if not valid, true otherwise
 */
bool Display::validatePos(sf::CircleShape c1) {
    for (auto &e2: this->objects){
        if (&c1 != &std::get<0>(e2) && this->isCollisionWithBall(c1,std::get<0>(e2))) {
            return false;
        }
        if (this->isCollisionWithWall(c1)){
            return false;
        }
    }

    return true;

}


bool Display::isCollisionWithWall(sf::CircleShape c1){
    int posX = c1.getPosition().x;
    int posY = c1.getPosition().y;
    return  
        (posX < 0 || posX > (this->window.getSize().x -  2 * c1.getRadius())) 
        || 
        (posY < 0 || posY > (this->window.getSize().y - 2 * c1.getRadius()));
}