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
    int generateRelativeMovement(int direction_id);
    bool isValidMove(int &old_pos, int &new_pos);
    void handleMovement(int &new_pos, Particle *&particle);

public:
    Engine(Grid *&grid);
    void updateGrid();
};

#endif // ENGINE_H
