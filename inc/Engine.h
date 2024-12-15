#ifndef ENGINE_H
#define ENGINE_H

#include "ParticleStores/BaseParticleStore.h"
#include <cstdlib>
#include <cmath>
using namespace std;

class Engine
{
private:
    SpaceMetadata *space_data;
    int directions;
    BaseParticleStore *particle_store;
    int generateRelativeMovement(int direction_id);
    bool isValidMove(int &old_pos, int &new_pos);
    void handleMovement(int &new_pos, Particle *&particle);

public:
    Engine(BaseParticleStore *&particle_store, SpaceMetadata *space_data);
    void updateGrid();
};

#endif // ENGINE_H
