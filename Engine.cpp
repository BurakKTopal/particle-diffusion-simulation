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

int Engine::generateRelativeMovement(int direction_id)
{
    // cout << "direction id is " << direction_id << endl;
    if (direction_id < 0)
    {
        cout << "invalid direction id" << endl;
        exit(1);
    }
    return ((int)(direction_id / 3) - 1) * grid_width + (-1 + (direction_id % 3)); // maps 0->-w-1, 1->-w, 2->-w+1, 3->-1, 4->0, 5->1, 6->w-1, 7-> w, 8-> w + 1
}

bool Engine::isValidMove(int &old_pos, int &new_pos)
{
    if (new_pos < 0 || new_pos >= grid_height * grid_width)
        return false;

    int row_diff = abs(new_pos / grid_width - old_pos / grid_width);
    int col_diff = abs(new_pos % grid_width - old_pos % grid_width);

    return row_diff <= 1 && col_diff <= 1;
}
bool Engine::particleCanMove(Particle *particle)
{
    for (int id = 0; id < directions; id++)
    {
        if (id == 4) // Movement on itself, not considered as valid move
        {
            continue;
        }
        int particle_old_pos = particle->getPosition();
        int particle_new_pos = particle_old_pos + generateRelativeMovement(rand() % directions);
        if (!grid->checkIfDuplicatePosition(particle_new_pos) && isValidMove(particle_old_pos, particle_new_pos) && particle->getState() == MOVING)
        {
            return true;
        }
    }
    return false;
}
void Engine::initSeenMap()
{
    this->seen_particles.clear();
    this->seen_particles = unordered_map<int, Particle *>();
}

void Engine::updateGrid()
{
    size_t index = 0;
    Particle **particles = grid->getParticles();

    initSeenMap();
    while (particles[index] != nullptr)
    {
        int particle_new_pos = particles[index]->getPosition();
        if (particleCanMove(particles[index]))
        {
            int particle_old_pos = particles[index]->getPosition();

            cout << "particle is going to move" << endl;

            do
            {
                particle_new_pos = particles[index]->getPosition() + generateRelativeMovement(rand() % directions);
            } while (!isValidMove(particle_old_pos, particle_new_pos) || particle_new_pos - particle_old_pos == 0);
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
        seen_particles[particle->getPosition()] = particle;
    }
    else
    {
        particle->setPosition(new_pos);
        seen_particles[new_pos] = particle;
    }
}
