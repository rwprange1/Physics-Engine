#include "Display.h"


/**
 * The 
 */
Display::Display(){
    this->videoMode = sf::VideoMode({1000, 800});
    this->window = sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);
    this->buildCube();
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

    this->window.draw(this->cube);
    
    for (auto &e: this->objects){
        this->window.draw(std::get<0>(e));
    }


    this->window.display();
}

void Display::update(){
    this->pollEvents();

    this->updateCube();
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


    int numObjects = 1000 + (rand() % 10);
    for (int i = 0; i < numObjects; i++) {
        int color =  (1 + rand()) % 6; 
        sf::CircleShape circle; 
        
        circle.setRadius(25.f);
        //create a function which returns a random position not contained in the list, and not causing collisons

        circle.setPosition(sf::Vector2f(
            rand() % static_cast<int>(this->window.getSize().x - circle.getRadius()),
            rand() % static_cast<int>(this->window.getSize().y - circle.getRadius())
        ));
        circle.setFillColor(colors[color]);

        this->objects.push_back(std::make_tuple(circle, this->makeVec(circle) ));
    }
    std::cout << "Generated " + std::to_string(numObjects) << " balls :)\n";
}

/**
 * Create the cube which we will be launching at the other balls!
 * @returns void
 */
void Display::buildCube(){
    sf::Vector2u dimensions = this->window.getSize();
    this->cube.setPosition(sf::Vector2f(100.f,100.f)); //we are placing the object's top left corner here
    this->cube.setSize(sf::Vector2f(100.f,100.f)); //float value helps compiler
    this->cube.setScale(sf::Vector2f(.5f, .5f)); //cut the objects size down by 1/2
    this->cube.setFillColor(sf::Color::Cyan);
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

    for (auto &e: this->objects){
        std::get<0>(e).move(std::get<1>(e));
        int posX = std::get<0>(e).getPosition().x;
        int posY = std::get<0>(e).getPosition().y;
        if ( posX < 0 || posX > (this->window.getSize().x -  2 * std::get<0>(e).getRadius())){
            std::get<1>(e).x = std::get<1>(e).x * -1.f;
        }

        if ( posY < 0 || posY > (this->window.getSize().y - 2 * std::get<0>(e).getRadius())){
            std::get<1>(e).y = std::get<1>(e).y * -1.f;
        }
    }



}

void Display::updateCube(){

}