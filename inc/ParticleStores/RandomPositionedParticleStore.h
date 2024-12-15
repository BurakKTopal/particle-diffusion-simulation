#ifndef RANDOM_POSITIONED_PARTICLE_STORE
#define RANDOM_POSITIONED_PARTICLE_STORE

#include "BaseParticleStore.h"

class RandomPositionedParticleStore : public BaseParticleStore
{
public:
    RandomPositionedParticleStore(SpaceMetadata *space_data);
    ~RandomPositionedParticleStore();

private:
    void generateParticles(int &num_of_initial_particles);
    int generateRandomPositions(size_t case_id);
};

#endif // RANDOM_POSITIONED_PARTICLE_STORE