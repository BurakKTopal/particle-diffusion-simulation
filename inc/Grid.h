#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <map>
#include <vector>
#include "Particle.h"

using namespace std;

class Grid
{
private:
    int width;
    int height;
    int grid_len;
    Particle **particles;

private:
    int generateRandomPosOnEdge(size_t case_id);
    void initParticles(int &num_of_initial_particles);

public:
    bool checkIfDuplicatePosition(int position);
    Grid(int width, int height);
    void initialize(float density);
    void print();
    Particle **getParticles();
    void display();
    int getWidth();
    int getHeight();
    bool reachedTerminalState();
    Particle *getParticleByPosition(int &position);
    ~Grid();
};

#endif // GRID_H
