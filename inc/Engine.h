#ifndef ENGINE_H
#define ENGINE_H

#include "Grid.h"
#include <unordered_map>
using namespace std;

class Engine
{
private:
    int grid_width;
    int grid_height;
    size_t directions;
    unordered_map<int, Particle *> seen_particles;
    Grid *grid;

    int generateRelativeMovement(size_t direction_id);
    bool moveStaysWithinGrid(int new_pos);
    void handleMovement(int &new_pos, Particle *&particle);

public:
    Engine(Grid *&grid);
    void updateGrid();
};

#endif // ENGINE_H
