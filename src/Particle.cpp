#include "../inc/Particle.h"

Particle::Particle(int position, State state) : position(position), state(state)
{
    std::cout << "Initialized particle at position " << position << std::endl;
}

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
