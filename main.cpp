#include <iostream>
#include "Display.h"


using namespace sf;

int main(){
    
    //init rand
    std::srand(static_cast<unsigned>(time(NULL)));

    Display simulation;

    while(simulation.isWinOpen()){
        simulation.update();
        simulation.render(); 
    }
    

}