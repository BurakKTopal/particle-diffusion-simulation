#include <iostream>
#include "inc/Particle.h"

using namespace std;

Particle::Particle(int position) : position(position)
{
    cout << "Initialized particle at position " << position << endl;
    this->state = MOVING;
};

void Particle::setPosition(int position)
{
    this->position = position;
};

int Particle::getPosition()
{
    return position;
};

State Particle::getState()
{
    return state;
};

void Particle::setState(State state)
{
    this->state = state;
}
