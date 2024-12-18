#include "../../inc/ParticleStores/ParticleStoreFactory.h"
#include "../../inc/ParticleStores/EdgePositionedParticleStore.h"
#include "../../inc/ParticleStores/RandomPositionedParticleStore.h"

namespace ParticleStoreFactory
{
    BaseParticleStore *initialize(ParticleStoreType type, SpaceMetadata *space_data)
    {
        switch (type)
        {
        case RANDOM:
            return new RandomPositionedParticleStore(space_data);

        case EDGE:
            return new EdgePositionedParticleStore(space_data);

        default:
            return new RandomPositionedParticleStore(space_data); // Fallback to RANDOM
        }
    }
}