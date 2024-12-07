#include "../../inc/Grids/RandomGrid.h"

RandomGrid::RandomGrid(int width, int height) : BaseGrid(width, height)
{
}

void RandomGrid::generateParticles(int &num_of_initial_particles)
{
    for (size_t i = 0; i < num_of_initial_particles; i++)
    {
        int particle_pos = generateRandomPositions(4);
        while (checkIfDuplicatePosition(particle_pos))
        {
            particle_pos = generateRandomPositions(4);
            cout << "duplicate " << particle_pos << " !!!" << endl;
        }
        particles[i] = new Particle(particle_pos);
    }
}

RandomGrid::~RandomGrid()
{
}
