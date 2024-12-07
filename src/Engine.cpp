#include "../inc/Engine.h"
#include "../inc/Grids/BaseGrid.h"
#include <cstdlib>
using namespace std;

Engine::Engine(BaseGrid *&grid) : grid{grid}
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

void Engine::updateGrid()
{
    size_t index = 0;
    Particle **particles = grid->getParticles();

    while (particles[index] != nullptr)
    {
        int particle_new_pos = particles[index]->getPosition();
        if (particles[index]->getState() == MOVING)
        {
            int particle_old_pos = particles[index]->getPosition();
            do
            {
                particle_new_pos = particle_old_pos + generateRelativeMovement(rand() % directions);
            } while (!isValidMove(particle_old_pos, particle_new_pos) || particle_new_pos - particle_old_pos == 0);
        }

        handleMovement(particle_new_pos, particles[index]);
        index++;
    }
}

void Engine::handleMovement(int &new_pos, Particle *&particle)
{
    Particle *colliding_particle = grid->getParticleByPosition(new_pos);

    if (colliding_particle != NULL)
    {
        colliding_particle->setState(STATIONARY);
        particle->setState(STATIONARY);
    }
    else
    {
        particle->setPosition(new_pos);
    }
}