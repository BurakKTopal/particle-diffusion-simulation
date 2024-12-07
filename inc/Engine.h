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
    int directions;
    Grid *grid;
    bool particleCanMove(Particle *particle);
    int generateRelativeMovement();
    bool isValidMove(int &old_pos, int &new_pos);
    void handleMovement(int &new_pos, Particle *&particle);
    void initSeenMap();

public:
    unordered_map<int, Particle *> seen_particles;

    Engine(Grid *&grid);
    void updateGrid();
};

#endif // ENGINE_H
