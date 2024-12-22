#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>

using namespace std;
enum State
{
    MOVING,
    STATIONARY
};

class Particle
{
private:
    int id;
    int position;
    State state;

public:
    Particle(int position, State state = MOVING);
    void setPosition(int position);
    int getPosition();
    State getState();
    void setState(State state);
};

#endif // PARTICLE_H