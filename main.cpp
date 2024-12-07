#include <iostream>
#include "inc/Grid.h"
#include "inc/Particle.h"
#include "inc/Engine.h"

int main()
{
    srand(time(0)); // initializer for time
    Grid *grid = new Grid(45, 45);
    grid->initialize(0.07);
    grid->display();
    cout << "Start engine..." << endl;
    Engine *engine = new Engine(grid);

    int iteration = 1;
    while (!grid->reachedTerminalState())
    {
        cout << "ITERATION " << iteration << endl;
        engine->updateGrid();
        grid->display();
        iteration++;
    }
    cout << "FINAL GRID" << endl;
    grid->display();

    delete grid;
}