#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <tuple>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Display {

    private:
        sf::RenderWindow window;
        sf::VideoMode videoMode;
        sf::Vector2i mousePosWindow; // mouse pos rel to window
        sf::Vector2f mousePosView; 

        std::vector< std::tuple<sf::CircleShape, sf::Vector2f>> objects;
        sf::RectangleShape cube;
        
     

        //Functions
        void buildObjects();
        void buildCube();
        void updateObjects();
        void updateCube();

        sf::Vector2f makeVec(sf::CircleShape);

    public:
        Display();
        


        //Functions
        void update();
        void render();
        void pollEvents();
        bool isWinOpen();

        
};