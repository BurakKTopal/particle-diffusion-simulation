#ifndef CENTER_EDGE_POSITIONED_PARTICLE_STORE
#define CENTER_EDGE_POSITIONED_PARTICLE_STORE

#include "EdgePositionedParticleStore.h"
#include <unordered_map>
#include <iostream>
using namespace std;

class CenterEdgePositionedParticleStore : public EdgePositionedParticleStore
{
public:
    int density_center_particles;
    CenterEdgePositionedParticleStore(SpaceMetadata *space_data);
    ~CenterEdgePositionedParticleStore();
    void initialize(float edge_density, float center_density);
    void initialize(float density) override;

private:
    void checkCenterDensity(float num_center_particles);
    void generateParticles(int num_of_edge_particles, int num_of_center_particles);
    void generateCenterParticles(int num_edge_particles, int num_center_particles);
};

#endif