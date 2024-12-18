#include "../../inc/ParticleStores/RandomPositionedParticleStore.h"

RandomPositionedParticleStore::RandomPositionedParticleStore(SpaceMetadata *space_data) : BaseParticleStore(space_data)
{
}

void RandomPositionedParticleStore::generateParticles(int &num_of_initial_particles)
{
    int random_number = 0;
    int particle_pos = 0;
    for (size_t i = 0; i < num_of_initial_particles; i++)
    {
        do
        {
            random_number = (rand() + 1); // +1 to not give more chance for 0
            particle_pos = random_number % n_of_boxes;
        } while (checkIfDuplicatePosition(particle_pos));
        particles[i] = new Particle(particle_pos);
    }
}

RandomPositionedParticleStore::~RandomPositionedParticleStore()
{
}
