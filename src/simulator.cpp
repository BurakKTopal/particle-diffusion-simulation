

#include <iostream>
#include "inc/Grids/EdgeGrid.h"
#include "inc/Grids/BaseGrid.h"
#include "inc/Grids/RandomGrid.h"
#include "inc/Particle.h"
#include "inc/Engine.h"

int main()
{
    srand(time(0)); // initializer for time
    BaseGrid *grid = new EdgeGrid(400, 400);

    grid->initialize(0.005);
    grid->display();
    cout << "Start engine..." << endl;
    Engine *engine = new Engine(grid);

    int iteration = 1;
    while (!grid->reachedTerminalState())
    {
        // cout << "ITERATION " << iteration << endl;
        engine->updateGrid();
        // grid->display();
        iteration++;
    }
    cout << "FINAL GRID" << endl;
    grid->display();

    delete grid;
    delete engine;
}
