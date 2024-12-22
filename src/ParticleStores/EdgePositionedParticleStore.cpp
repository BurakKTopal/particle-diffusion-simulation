#include "../../inc/ParticleStores/EdgePositionedParticleStore.h"

EdgePositionedParticleStore::EdgePositionedParticleStore(SpaceMetadata *space_data) : BaseParticleStore(space_data)
{
}
void EdgePositionedParticleStore::generateParticles(int &num_of_initial_particles)
{
    size_t direction_id = 0;
    for (size_t i = 0; i < num_of_initial_particles; i++)
    {
        int particle_pos = generateRandomEdgePosition(direction_id % 4);
        int num_call_in_edge = 1;
        while (checkIfDuplicatePosition(particle_pos))
        {
            if (num_call_in_edge > max(space_data->getWidth(), space_data->getHeight()))
            {
                num_call_in_edge = 1;
                direction_id += 1;
                break;
            }
            particle_pos = generateRandomEdgePosition(direction_id % 4);
            num_call_in_edge++;
        }
        particles[i] = new Particle(particle_pos);
        direction_id++;
    }
}

void EdgePositionedParticleStore::checkDensity(float &density)
{
    BaseParticleStore::checkDensity(density); // Base class check
    int num_of_initial_particles = int(density * n_of_boxes);
    int width = space_data->getWidth();
    int height = space_data->getHeight();
    if (num_of_initial_particles > 2 * (width + height) - 4)
    {
        displayErrorAndExit("Too much boundary particles. Maximally " + to_string((float)(2 * (width + height) - 4) / (height * width)));
    }
}
int EdgePositionedParticleStore::generateRandomEdgePosition(size_t case_id)
{
    int pos;
    int random_number = (rand() + 1); // +1 to not give more chance for 0
    int width = space_data->getWidth();
    int height = space_data->getHeight();
    switch (case_id)
    {
    case 0:
        pos = random_number % width;
        break;
    case 1:
        pos = (width - 1) + (random_number % height) * width;
        break;
    case 2:
        pos = (random_number % width) + (height - 1) * (width);
        break;
    case 3:
        pos = (random_number % height) * (width);
        break;
    default:
        break;
    }
    return pos;
}

EdgePositionedParticleStore::~EdgePositionedParticleStore()
{
}
