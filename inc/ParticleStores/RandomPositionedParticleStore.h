#ifndef RANDOM_POSITIONED_PARTICLE_STORE
#define RANDOM_POSITIONED_PARTICLE_STORE

#include "BaseParticleStore.h"

class RandomPositionedParticleStore : public BaseParticleStore
{
public:
    RandomPositionedParticleStore(int width, int height);
    ~RandomPositionedParticleStore();

private:
    void generateParticles(int &num_of_initial_particles);
};

#endif // RANDOM_POSITIONED_PARTICLE_STORE
