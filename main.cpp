#include <iostream>
#include "inc/Grid.h"
#include "inc/Particle.h"
#include "inc/Engine.h"

int main()
{
    srand(time(0)); // initializer for time
    Grid *grid = new Grid(3, 3);
    grid->initialize(0.8);
    grid->print();


    
    cout << "Start engine" << endl;
    Engine *engine = new Engine(grid);
    engine->updateGrid();
    grid->print();

    delete grid;
}