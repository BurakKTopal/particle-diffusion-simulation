#ifndef ENGINE_H
#define ENGINE_H

#include "Grids/BaseGrid.h"
using namespace std;

class Engine
{
private:
    int grid_width;
    int grid_height;
    int directions;
    BaseGrid *grid;
    int generateRelativeMovement(int direction_id);
    bool isValidMove(int &old_pos, int &new_pos);
    void handleMovement(int &new_pos, Particle *&particle);

public:
    Engine(BaseGrid *&grid);
    void updateGrid();
};

#endif // ENGINE_H
