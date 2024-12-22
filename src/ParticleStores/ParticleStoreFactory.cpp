#include "../../inc/ParticleStores/ParticleStoreFactory.h"
#include "../../inc/ParticleStores/EdgePositionedParticleStore.h"
#include "../../inc/ParticleStores/RandomPositionedParticleStore.h"
#include "../../inc/ParticleStores/CenterEdgePositionedParticleStore.h"

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

        case CENTER_EDGE:
            return new CenterEdgePositionedParticleStore(space_data);

        default:
            return new RandomPositionedParticleStore(space_data); // Fallback to RANDOM
        }
    }
}