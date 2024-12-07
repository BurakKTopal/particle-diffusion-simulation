#include <iostream>
#include "inc/Grids/EdgeGrid.h"
#include "inc/Grids/BaseGrid.h"
#include "inc/Grids/RandomGrid.h"
#include "inc/Particle.h"
#include "inc/Engine.h"

int main()
{
    srand(time(0)); // initializer for time
    BaseGrid *grid = new RandomGrid(80, 40);

    grid->initialize(0.06);
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