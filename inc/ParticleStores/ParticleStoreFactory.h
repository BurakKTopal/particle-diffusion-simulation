#ifndef PARTICLE_STORE_FACTORY_H
#define PARTICLE_STORE_FACTORY_H

#include "BaseParticleStore.h"

enum ParticleStoreType
{
    RANDOM,
    EDGE,
    CENTER_EDGE, // Also corresponds to DLA
    DEFAULT
};

namespace ParticleStoreFactory
{
    BaseParticleStore *initialize(ParticleStoreType type, SpaceMetadata *space_data);
}

#endif // PARTICLE_STORE_FACTORY_H