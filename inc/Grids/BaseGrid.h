#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <map>
#include <vector>
#include "../Particle.h"

using namespace std;

class BaseGrid
{
private:
    int grid_len;

protected:
    int width;
    int height;
    Particle **particles;

private:
    void initParticles(int &num_of_initial_particles);

protected:
    int generateRandomPositions(size_t case_id);

    virtual void generateParticles(int &num_of_initial_particles) = 0;

public:
    bool checkIfDuplicatePosition(int position);
    BaseGrid(int width, int height);
    void initialize(float density);
    void print();
    Particle **getParticles();
    void display();
    int getWidth();
    int getHeight();
    bool reachedTerminalState();
    Particle *getParticleByPosition(int &position);
    virtual ~BaseGrid();
};

#endif // GRID_H
