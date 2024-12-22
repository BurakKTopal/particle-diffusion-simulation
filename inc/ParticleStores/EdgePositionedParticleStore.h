#ifndef EDGE_POSITIONED_PARTICLE_STORE
#define EDGE_POSITIONED_PARTICLE_STORE

#include "BaseParticleStore.h"

class EdgePositionedParticleStore : public BaseParticleStore
{
public:
    EdgePositionedParticleStore(SpaceMetadata *space_data);
    void checkDensity(float &density) override;
    ~EdgePositionedParticleStore();

protected:
    void generateParticles(int &num_of_initial_particles) override;

private:
    int generateRandomEdgePosition(size_t case_id);
};

#endif