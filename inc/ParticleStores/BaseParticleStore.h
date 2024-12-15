#ifndef GRID_H
#define GRID_H

#include <iostream>
#include "../Particle.h"
#include <GLFW/glfw3.h>
#include <vector>
using namespace std;

class BaseParticleStore
{
protected:
    int grid_len;
    int width;
    int height;
    Particle **particles;

private:
    void initParticles(int &num_of_initial_particles);

protected:
    int generateRandomPositions(size_t case_id);

    virtual void generateParticles(int &num_of_initial_particles) = 0;
    virtual void additionalDensityCheck(float &density) {};

public:
    bool checkIfDuplicatePosition(int position);
    BaseParticleStore(int width, int height);
    void initialize(float density);
    Particle **getParticles();
    int getWidth();
    int getHeight();
    bool reachedTerminalState();
    Particle *getParticleByPosition(int &position);

    virtual ~BaseParticleStore();
};

#endif // GRID_H
