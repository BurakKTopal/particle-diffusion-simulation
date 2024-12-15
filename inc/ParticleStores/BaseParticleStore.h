#ifndef BASE_PARTICLE_STORE
#define BASE_PARTICLE_STORE

#include <iostream>
#include "../Particle.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "../SpaceInformation.h"

using namespace std;

class BaseParticleStore
{
protected:
    int n_of_boxes;
    SpaceMetadata *space_data;
    Particle **particles;

private:
    void initParticles(int &num_of_initial_particles);

protected:

    virtual void generateParticles(int &num_of_initial_particles) = 0;
    virtual void additionalDensityCheck(float &density) {};

public:
    bool checkIfDuplicatePosition(int position);
    BaseParticleStore(SpaceMetadata *space_data);
    void initialize(float density);
    Particle **getParticles();
    // int getWidth();
    // int getHeight();
    bool reachedTerminalState();
    Particle *getParticleByPosition(int &position);

    virtual ~BaseParticleStore();
};

#endif // GRID_H
