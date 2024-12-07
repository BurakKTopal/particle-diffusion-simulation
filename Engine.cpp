#include "inc/Engine.h"
#include "inc/Grid.h"
#include <cstdlib>
using namespace std;

Engine::Engine(Grid *&grid) : grid{grid}
{
    directions = 8;
    grid_width = grid->getWidth();
    grid_height = grid->getHeight();
}

int Engine::generateRelativeMovement(size_t direction_id)
{
    int to_left_corner_movement = -grid_height - 1;
    int relative_movement = to_left_corner_movement + direction_id;
    return relative_movement;
}

bool Engine::moveStaysWithinGrid(int new_pos)
{
    return new_pos >= 0 && new_pos < grid_height * grid_width;
}

void Engine::updateGrid()
{
    size_t index = 0;
    Particle **particles = grid->getParticles();
    // grid->print();
    while (particles[index] != nullptr)
    {
        if (particles[index]->getState() == STATIONARY)
        {
            index++;
            continue;
        }

        int particle_new_pos = particles[index]->getPosition() + generateRelativeMovement(rand() % directions);

        while (!moveStaysWithinGrid(particle_new_pos))
        {
            cout << "not valid move! " << particle_new_pos << endl;
            particle_new_pos = particles[index]->getPosition() + generateRelativeMovement(rand() % directions);
        }
        handleMovement(particle_new_pos, particles[index]);
        index++;
    }
}

void Engine::handleMovement(int &new_pos, Particle *&particle)
{
    if (seen_particles.find(new_pos) != seen_particles.end())
    {
        seen_particles[new_pos]->setState(STATIONARY);
        particle->setState(STATIONARY);
    }
    else
    {
        particle->setPosition(new_pos);
        seen_particles[new_pos] = particle;
    }
}
