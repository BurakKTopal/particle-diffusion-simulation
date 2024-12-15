#include "../inc/Engine.h"

Engine::Engine(BaseParticleStore *&particle_store, SpaceMetadata *space_data) : particle_store{particle_store}, space_data{space_data}
{
    directions = pow((space_data->getDimension()), 3) - 1;
}

int Engine::generateRelativeMovement(int direction_id)
{
    // cout << "direction id is " << direction_id << endl;
    if (direction_id < 0)
    {
        cout << "invalid direction id" << endl;
        exit(1);
    }
    return ((int)(direction_id / 3) - 1) * space_data->getWidth() + (-1 + (direction_id % 3)); // maps 0->-w-1, 1->-w, 2->-w+1, 3->-1, 4->0, 5->1, 6->w-1, 7-> w, 8-> w + 1
}

bool Engine::isValidMove(int &old_pos, int &new_pos)
{
    if (new_pos < 0 || new_pos >= space_data->getNumberOfBoxes())
        return false;
    int grid_width = space_data->getWidth();
    int row_diff = abs(new_pos / grid_width - old_pos / grid_width);
    int col_diff = abs(new_pos % grid_width - old_pos % grid_width);

    return row_diff <= 1 && col_diff <= 1;
}

void Engine::updateGrid()
{
    size_t index = 0;
    Particle **particles = particle_store->getParticles();

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
    Particle *colliding_particle = particle_store->getParticleByPosition(new_pos);

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