#include "../../inc/ParticleStores/RandomPositionedParticleStore.h"

RandomPositionedParticleStore::RandomPositionedParticleStore(int width, int height) : BaseParticleStore(width, height)
{
}

void RandomPositionedParticleStore::generateParticles(int &num_of_initial_particles)
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

RandomPositionedParticleStore::~RandomPositionedParticleStore()
{
}
