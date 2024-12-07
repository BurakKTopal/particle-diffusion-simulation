#ifndef RANDOM_GRID_H
#define RANDOM_GRID_H

#include "BaseGrid.h"

class RandomGrid : public BaseGrid
{
public:
    RandomGrid(int width, int height);
    ~RandomGrid();

private:
    void generateParticles(int &num_of_initial_particles);
};

#endif // RANDOM_GRID_H
